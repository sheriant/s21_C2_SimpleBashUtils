#ifndef S21_GREP_H
#define S21_GREP_H
#define _GNU_SOURCE

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <getopt.h>
#include <regex.h>
#include <string.h>

typedef struct {
  bool e, i, v, c, l, n;
  bool h, s, f, o;
  char *pattern;
  char *pattern_file;
} Options;

bool parser(int argc, char *argv[], Options *flags);
void grep(int argc, char *argv[], Options *flags);
bool handle_pattern_file(Options *flags);
int process_file(const char *filename, regex_t *regex, Options *flags, int file_count);

#endif