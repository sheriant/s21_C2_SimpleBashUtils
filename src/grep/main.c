#include <stdio.h>
#include <getopt.h>
#include <stdbool.h>
#include <regex.h>


typedef struct {
  bool e, i, v, c, l, n;
  bool h, s, f, o;
  bool error;
  char *pattern;
  char *pattern_file;
} Options;

Options parser(int argc, char *argv[]);
void grep(int argc, char *argv[], Options *flags);
void output(int argc, char *argv[], Options flags);


int main(int argc, char *argv[]) {
  Options flags = (parser(argc, argv));
  if (flags) {
    grep(argc, argv, &flags);
  } else {
    fprintf(stderr, "Usage: %s [ivclnhsof:[file with patterns]e:[pattern]] template [file_name]\n", argv[0]);
  }
  return 0;
}

Options parser(int argc, char *argv[]) {
  Options flags = {0};
  int opt = 0;
  while ((opt = getopt(argc, argv, "ivclnhsof:e:")) != -1) {
    switch (opt) {
      case 'i':
        flags.i = true;
        break;
      case 'v':
        flags.v = true;
        break;
      case 'c':
        flags.c = true;
        break;
      case 'l':
        flags.l = true;
        break;
      case 'n':
        flags.n = true;
        break;
      case 'h':
        flags.h = true;
        break;
      case 's':
        flags.s = true;
        break;
      case 'o':
        flags.o = true;
        break;
      case 'e':
        flags.e = true;
        flags.pattern = optarg;
        break;
      case 'f':
        flags.f = true;
        flags.pattern_file = optarg;
        break;
      default:
        flags.error = true;
        break;
    }
  }
  if (flags.pattern == NULL) flags.pattern = argv[optind++]; 
  return flags;
}

void grep(int argc, char *argv[], Options *flags) {
  printf("%d - количество аргументов\n%s - аргумент optind должен вернуть файл где ищем\n", argc, argv[optind]);
  printf("%d - флаг c\n", flags->c);
  printf("%d - флаг h\n", flags->h);
  printf("%d - флаг i\n", flags->i);
  printf("%d - флаг e: %s (паттерн)\n", flags->e, optarg);
  printf("%d - флаг f: %s (файл с паттернами)\n", flags->f, optarg);
}

void process_file (Options flags, char *path, regex_t* regular) {

}

void output(int argc, char *argv[], Options flags) {
  Options flags = parser(argc, argv);
  regex_t regular = {0};
  int error = regcomp(&regular, flags.pattern, 0);
  if (error) perror("Error");
}