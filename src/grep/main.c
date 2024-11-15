#include <stdio.h>
#include <getopt.h>
#include <stdbool.h>
#include <regex.h>


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
    fprintf(stderr, "Usage: %s [-] template [file_name]\n", argv[0]);
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

void grep(int argc, char *argv[], Options *flags) {
  if (flags->e && optind < argc) {
    flags.pattern = argv[optind];
    optind++;
    } else if (flags->f && optind < argc) {
      flags->pattern_file = argv[optind];
      optind++;
    }

    regex_t regex;
    int cflags = REG_EXTENDED | (flags.i_flag ? REG_ICASE : 0);

    if (regcomp(&regex, flags.pattern, cflags) != 0) {
        fprintf(stderr, "Failed to compile regex\n");
    } else {

    }
    fprintf(stderr, "Error opening file %s\n", argv[optind]);

}
