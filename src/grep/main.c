#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct {
  bool e, i, v, c, l, n;
  bool h, s, f, o;
  char *pattern;
  char *pattern_file;
} Options;

bool parser(int argc, char *argv[], Options *flags);
void grep(int argc, char *argv[], Options *flags);
//void output(FILE *f, Options *flags);


int main(int argc, char *argv[]) {
  Options flags = {0};
  if (!(parser(argc, argv, &flags))) {
    grep(argc, argv, &flags);
  } else {
    fprintf(stderr, "Usage: %s [-] [file ...]\n", argv[0]);
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

  return error_flag;
}