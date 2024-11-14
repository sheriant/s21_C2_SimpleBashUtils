#ifndef MAIN_H
#define MAIN_H

#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct {
  bool b, E, n, s, T, v;
} Options;

void check_option(int *current_char, int *prev_char, Options flags, FILE f);
bool parser(int argc, char *argv[], Options *flags);
void output(FILE *f, Options *flags);
void cat(int argc, char *argv[], Options *flags);

int flag_b_or_n(int line_counter);
int flag_v(int current_char);

#endif
