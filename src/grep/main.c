#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct {
  bool e, i, v, c, l, n;
  bool h, s, f, o;
  char *pattern;
  char *pattern_file;
} Options;

void parser(int argc, char *argv[], Options *flags);
//void output(FILE *f, Options *flags);
//void grep(int argc, char *argv[], Options *flags);


int main(int argc, char *argv[]) {
  Options flags = {0};

  return 0;
}

bool parser(int argc, char *argv[], Options *flags) {
  bool error_flag = false;
  int opt = 0;
  while ((opt = getopt(argc, argv, "e:ivcln")) != -1 && !error_flag) {
    switch (opt) {
      case 'e':
        flags->e = true;
        break;
      case 'i':
        flags->E = true;
        flags->v = true;
        break;
      case 'v':
        flags->E = true;
        break;
      case 'c':
        flags->n = true;
        break;
      case 'l':
        flags->s = true;
        break;
      case 'n':
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