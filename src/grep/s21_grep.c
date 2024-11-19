#include "s21_grep.h"

int main(int argc, char *argv[]) {
  Options flags = {0};
  if (parser(argc, argv, &flags)) {
    fprintf(stderr, "Usage: %s [OPTION]... PATTERNS [FILE]...\n", argv[0]);
  } else if (optind == argc) {
    char *argv_new[] = {argv[0], "-"};
    grep(2, argv_new, &flags);
  } else {
    grep(argc, argv, &flags);
  }
  free(flags.pattern);
  return 0;
}

bool parser(int argc, char *argv[], Options *flags) {
  bool error_flag = false;
  int opt = 0;
  while ((opt = getopt(argc, argv, "ivclnhsof:e:")) != -1) {
    switch (opt) {
      case 'i':
        flags->i = true;
        break;
      case 'v':
        flags->v = true;
        break;
      case 'c':
        flags->c = true;
        break;
      case 'l':
        flags->l = true;
        break;
      case 'n':
        flags->n = true;
        break;
      case 'h':
        flags->h = true;
        break;
      case 's':
        flags->s = true;
        break;
      case 'o':
        flags->o = true;
        break;
      case 'e':
        flags->e = true;
        flags->pattern = strdup(optarg);
        break;
      case 'f':
        flags->f = true;
        flags->pattern_file = strdup(optarg);
        break;
      default:
        error_flag = true;
        break;
    }
  }
  if (flags->f && !error_flag) error_flag = handle_pattern_file(flags);
  if (!flags->pattern && optind < argc) flags->pattern = strdup(argv[optind++]);
  if (!flags->pattern) error_flag = true;
  return error_flag;
}

bool handle_pattern_file(Options *flags) {
  bool error_flag = false;
  FILE *pattern_file = fopen(flags->pattern_file, "r");
  if (!pattern_file) {
    if (!flags->s) {
      fprintf(stderr, "s21_grep: %s: No such file or directory\n",
              flags->pattern_file);
    }
    return true;
  }
  char buffer[4096];
  if (fgets(buffer, sizeof(buffer), pattern_file)) {
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
      buffer[len - 1] = '\0';
    }
    flags->pattern = strdup(buffer);
    if (!flags->pattern) {
      error_flag = true;
    }
  } else {
    error_flag = true;
  }
  fclose(pattern_file);
  return error_flag;
}

void grep(int argc, char *argv[], Options *flags) {
  regex_t regex;
  int reti = regcomp(&regex, flags->pattern, flags->i ? REG_ICASE : 0);
  if (reti) {
    char msgbuf[100];
    regerror(reti, &regex, msgbuf, sizeof(msgbuf));
    fprintf(stderr, "Regex compilation failed: %s\n", msgbuf);
    exit(1);
  }

  int file_count = argc - optind;
  for (int i = optind; i < argc; i++) {
    if (process_file(argv[i], &regex, flags, file_count)) {
      if (!flags->s)
        fprintf(stderr, "s21_grep: %s: No such file or directory\n", argv[i]);
    }
  }
  regfree(&regex);
}

int process_file(const char *filename, regex_t *regex, Options *flags,
                 int file_count) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    if (!flags->s) {
      fprintf(stderr, "s21_grep: %s: No such file or directory\n", filename);
    }
    return 1;
  }

  char buffer[4096];
  int line_number = 0, match_count = 0;
  bool file_has_match = false;

  while (fgets(buffer, sizeof(buffer), file)) {
    line_number++;
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
      buffer[len - 1] = '\0';
    }
    process_line(buffer, line_number, filename, regex, flags, file_count,
                 &match_count, &file_has_match);
  }

  if (flags->c) {
    if (!flags->h && file_count > 1) {
      printf("%s:", filename);
    }
    printf("%d\n", match_count);
  }

  if (flags->l && file_has_match) {
    printf("%s\n", filename);
  }

  fclose(file);
  return 0;
}

void process_line(const char *line, int line_number, const char *filename,
                  regex_t *regex, Options *flags, int file_count,
                  int *match_count, bool *file_has_match) {
  bool line_matches = match_line(line, regex, flags);

  if (line_matches) {
    (*match_count)++;
    *file_has_match = true;

    if (!flags->c && !flags->l) {
      if (flags->o) {
        print_matches_only(line, regex);
      } else {
        print_line(line, line_number, filename, flags, file_count);
      }
    }
  }
}

bool match_line(const char *line, regex_t *regex, Options *flags) {
  int reti = regexec(regex, line, 0, NULL, 0);
  return (!reti && !flags->v) || (reti == REG_NOMATCH && flags->v);
}

void print_line(const char *line, int line_number, const char *filename,
                Options *flags, int file_count) {
  if (!flags->h && file_count > 1) {
    printf("%s:", filename);
  }
  if (flags->n) {
    printf("%d:", line_number);
  }
  printf("%s\n", line);
}

void print_matches_only(const char *line, regex_t *regex) {
  regmatch_t match;
  const char *ptr = line;
  while (regexec(regex, ptr, 1, &match, 0) == 0) {
    printf("%.*s\n", (int)(match.rm_eo - match.rm_so), ptr + match.rm_so);
    ptr += match.rm_eo;
  }
}