#include "s21_grep.h"

int main(int argc, char *argv[]) {
  Options flags = {0};
  if (parser(argc, argv, &flags)) {
    fprintf(stderr,
            "Usage: %s [ivclnhsof:[file with patterns]e:[pattern]] template "
            "[file_name]\n",
            argv[0]);
    return 1;
  }

  if (optind == argc) {
    // Если нет файлов для поиска, читаем из stdin
    char *argv_new[] = {argv[0], "-"};
    grep(2, argv_new, &flags);
  } else {
    grep(argc, argv, &flags);
  }

  return 0;
}

bool parser(int argc, char *argv[], Options *flags) {
  bool error_flag = false;
  int opt = 0;
  while ((opt = getopt(argc, argv, "ivclnhsof:e:")) != -1 && !error_flag) {
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
        flags->pattern = optarg;
        break;
      case 'f':
        flags->f = true;
        flags->pattern_file = optarg;
        break;
      default:
        error_flag = true;
        break;
    }
  }

  if (flags->f) {
    error_flag = handle_pattern_file(flags);
  }

  if (flags->pattern == NULL && optind < argc) {
    flags->pattern = argv[optind++];
  }

  if (flags->pattern == NULL) {
    error_flag = true;
  }

  return error_flag;
}

bool handle_pattern_file(Options *flags) {
  bool error_flag = false;
  FILE *pattern_file = fopen(flags->pattern_file, "r");
  if (pattern_file) {
    char *line = NULL;
    size_t len = 0;
    ssize_t read = getline(&line, &len, pattern_file);
    if (read != -1) {
      flags->pattern = strdup(line);
      if (flags->pattern[strlen(flags->pattern) - 1] == '\n') {
        flags->pattern[strlen(flags->pattern) - 1] = '\0';
      }
    } else {
      error_flag = true;
    }
    free(line);
    fclose(pattern_file);
  } else {
    fprintf(stderr, "Error opening pattern file %s\n", flags->pattern_file);
    error_flag = true;
  }
  return error_flag;
}

void grep(int argc, char *argv[], Options *flags) {
  regex_t regex;
  int reti;
  int exit_status = 0;

  reti = regcomp(&regex, flags->pattern, flags->i ? REG_ICASE : 0);
  if (reti == 0) {
    int file_count = argc - optind;
    for (int i = optind; i < argc && exit_status == 0; i++) {
      exit_status = process_file(argv[i], &regex, flags, file_count);
    }
    regfree(&regex);
  } else {
    char msgbuf[100];
    regerror(reti, &regex, msgbuf, sizeof(msgbuf));
    fprintf(stderr, "Regex compilation failed: %s\n", msgbuf);
    exit_status = 1;
  }

  if (exit_status != 0) {
    exit(exit_status);
  }
}

int process_file(const char *filename, regex_t *regex, Options *flags,
                 int file_count) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    if (!flags->s) {
      fprintf(stderr, "Error opening file %s\n", filename);
    }
    return 1;
  }

  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  int line_number = 0;
  int match_count = 0;
  bool file_has_match = false;

  while ((read = getline(&line, &len, file)) != -1) {
    line_number++;
    int reti = regexec(regex, line, 0, NULL, 0);
    bool line_matches =
        (!reti && !flags->v) || (reti == REG_NOMATCH && flags->v);

    if (line_matches) {
      match_count++;
      file_has_match = true;

      if (!flags->c && !flags->l) {
        if (!flags->h && file_count > 1) {
          printf("%s:", filename);
        }
        if (flags->n) {
          printf("%d:", line_number);
        }
        printf("%s", line);
        if (line[strlen(line) - 1] != '\n') {
          printf("\n");
        }
      }
    }
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

  free(line);
  fclose(file);
  return 0;
}