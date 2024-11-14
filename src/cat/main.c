#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  bool b, E, n, s, T, v;
} Options;

void check_option(int *current_char, int *prev_char, Options flags, FILE f);
bool parser(int argc, char *argv[], Options *flags);
void output(FILE *f, Options *flags);
void cat(int argc, char *argv[], Options *flags);

int flag_b_or_n(int line_counter);
void flag_e();
void flag_t();
int flag_v(int current_char);
int flag_s(int current_char);

int main(int argc, char *argv[]) {
  Options flags = {false};
  bool error = parser(argc, argv, &flags);
  if (!error) {
    cat(argc, argv, &flags);
  } else {
    fprintf(stderr, "Usage: %s [-bEensTtv] [file ...]\n", argv[0]);
  }
  return 0;
}

bool parser(int argc, char *argv[], Options *flags) {
  struct option long_options[] = {{"number-nonblank", 0, NULL, 'b'},
                                  {"number", 0, NULL, 'n'},
                                  {"squeeze-blank", 0, NULL, 's'},
                                  {NULL, 0, NULL, 0}};

  bool error_flag = false;
  int opt;
  while ((opt = getopt_long(argc, argv, "beEnstTv", long_options, NULL)) !=
             -1 &&
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
      case '?':
        error_flag = true;
        break;
      default:
        error_flag = true;
        break;
    }
  }

  if (flags->b) flags->n = false;
  return error_flag;
}

void cat(int argc, char *argv[], Options *flags) {
  int index;
  if (optind) {
    index = optind;
  } else {
    index = 1;
  }
  for (; index < argc; index++) {
    FILE *f = fopen(argv[index], "r");
    if (f != NULL) {
      output(f, flags);
      fclose(f);
    } else {
      fprintf(stderr, "Error opening file %s\n", argv[index]);
    }
  }
}

void output(FILE *f, Options *flags) {
  int current_char;
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
      flag_e();
    } else if (flags->T && current_char == '\t') {
      flag_t();
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
void flag_e() { printf("$"); }
void flag_t() { printf("^I"); }

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