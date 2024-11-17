#include "main.h"

int main(int argc, char const *argv[]) {
  Options flags = {false};
  if (!(parser(argc, argv, &flags))) {
    cat(argc, argv, &flags);
  } else {
    fprintf(stderr, "Usage: %s [-bEensTtv] [file ...]\n", argv[0]);
  }
  return 0;
}

bool parser(int argc, char const *argv[], Options *flags) {
  struct option long_options[] = {{"number-nonblank", 0, NULL, 'b'},
                                  {"number", 0, NULL, 'n'},
                                  {"squeeze-blank", 0, NULL, 's'},
                                  {NULL, 0, NULL, 0}};

  bool error_flag = false;
  int opt = 0;
  while ((opt = getopt_long(argc, (char *const *)argv, "beEnstTv", long_options,
                            NULL)) != -1 &&
         !error_flag) {
    switch (opt) {
      case 'b':
        flags->b = true;
        break;
      case 'e':
        flags->E = true;
        flags->v = true;
        break;
      case 'E':
        flags->E = true;
        break;
      case 'n':
        flags->n = true;
        break;
      case 's':
        flags->s = true;
        break;
      case 't':
        flags->T = true;
        flags->v = true;
        break;
      case 'T':
        flags->T = true;
        break;
      case 'v':
        flags->v = true;
        break;
      default:
        error_flag = true;
        break;
    }
  }

  if (flags->b) flags->n = false;
  return error_flag;
}

void cat(int argc, char const *argv[], const Options *flags) {
  for (; optind < argc; optind++) {
    FILE *f = fopen(argv[optind], "r");
    if (f != NULL) {
      output(f, flags);
      fclose(f);
    } else {
      fprintf(stderr, "Error opening file %s\n", argv[optind]);
    }
  }
}

void output(FILE *f, const Options *flags) {
  int current_char = 0;
  int last_char = '\n';
  int line_counter = 1;
  int empty_line = 0;
  bool tab = {false};
  while ((current_char = fgetc(f)) != EOF) {
    if (flags->b && last_char == '\n' && current_char != '\n') {
      line_counter = flag_b_or_n(line_counter);
    } else if (flags->n && last_char == '\n') {
      line_counter = flag_b_or_n(line_counter);
    } else if (flags->s && current_char == '\n') {
      empty_line++;
    } else if (flags->E && current_char == '\n') {
      printf("$");
    } else if (flags->T && current_char == '\t') {
      printf("^I");
      tab = true;
    } else if (flags->v) {
      current_char = flag_v(current_char);
    }
    if (current_char != '\n') empty_line = 0;
    if (empty_line <= 2 && tab == false) fputc(current_char, stdout);
    last_char = current_char;
    tab = false;
  }
}

int flag_b_or_n(int line_counter) {
  printf("%6d\t", line_counter);
  line_counter++;
  return line_counter;
}

int flag_v(int current_char) {
  current_char = current_char & 0x7F;
  if (current_char > 127 && current_char < 160) printf("M-^");
  if (current_char < 32 && current_char != '\n' && current_char != '\t') {
    printf("^");
    current_char += 64;
  } else if (current_char == 127) {
    printf("^");
    current_char = '?';
  }
  return current_char;
}
