#ifndef MAIN_H
#define MAIN_H
#define _GNU_SOURCE

#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct {
  bool b, E, n, s, T, v;
} Options;

bool parser(int argc, char const *argv[], Options *flags);
void cat(int argc, char const *argv[], const Options *flags);
void output(FILE *f, const Options *flags);

int flag_b_or_n(int line_counter);
int flag_v(int current_char);

#endif
