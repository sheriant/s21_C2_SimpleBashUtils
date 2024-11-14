#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct {
  bool e, i, v, c, l, n;
  char *pattern;
} Options;

bool parser(int argc, char *argv[], Options *flags);
void output(FILE *f, Options *flags);
void grep(int argc, char *argv[], Options *flags);


int main(int argc, char *argv[]) {
  
  return 0;
}