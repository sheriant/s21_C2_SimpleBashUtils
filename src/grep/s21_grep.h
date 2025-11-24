#ifndef S21_GREP_H
#define S21_GREP_H

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif  // _POSIX_C_SOURCE

#include <getopt.h>  // Для работы с getopt (анализ аргументов командной строки)
#include <regex.h>  // Для работы с регулярными выражениями
#include <stdbool.h>  // Для использования типа bool
#include <stdio.h>    // Для стандартного ввода/вывода
#include <stdlib.h>  // Для функций работы с памятью, например malloc, free
#include <string.h>  // Для работы со строками, например strlen, strdup

typedef struct {
  bool i;  // Игнорировать регистр символов
  bool v;  // Инвертировать результат поиска
  bool c;  // Вывести только количество совпадений
  bool l;  // Вывести только имена файлов с совпадениями
  bool n;  // Печатать номера строк
  bool h;  // Не выводить имена файлов перед строками
  bool s;  // Подавить ошибки при работе с файлами
  bool o;  // Выводить только совпавшие части строки
  bool e;  // Указан шаблон через опцию -e
  bool f;  // Указан файл с шаблонами через опцию -f
  char *pattern;       // Шаблон поиска
  char *pattern_file;  // Имя файла с шаблонами
} Options;

bool parser(int argc, char *argv[], Options *flags);
bool handle_pattern_file(Options *flags);
void grep(int argc, char *argv[], Options *flags);
int process_file(const char *filename, regex_t *regex, Options *flags,
                 int file_count);
void process_line(const char *line, int line_number, const char *filename,
                  regex_t *regex, Options *flags, int file_count,
                  int *match_count, bool *file_has_match);
bool match_line(const char *line, regex_t *regex, Options *flags);
void print_line(const char *line, int line_number, const char *filename,
                Options *flags, int file_count);
void print_matches_only(const char *line, regex_t *regex);

#endif  // S21_GREP_H
