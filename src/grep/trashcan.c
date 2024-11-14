#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <regex.h>
#include <stdbool.h>
#include <getopt.h>

typedef struct {
    bool e_flag;
    bool i_flag;
    bool v_flag;
    bool c_flag;
    bool l_flag;
    bool n_flag;
    bool h_flag;
    bool s_flag;
    bool f_flag;
    bool o_flag;
    char *pattern;
    char *pattern_file;
} grep_flags;

void parse_flags(int argc, char *argv[], grep_flags *flags);
void grep_file(const char *filename, grep_flags *flags, regex_t *regex);

int main(int argc, char *argv[]) {
    grep_flags flags = {0};
    parse_flags(argc, argv, &flags);

    if (!flags.e_flag && optind < argc) {
        flags.pattern = argv[optind];
        optind++;
    }

    regex_t regex;
    int cflags = REG_EXTENDED | (flags.i_flag ? REG_ICASE : 0);

    if (regcomp(&regex, flags.pattern, cflags) != 0) {
        fprintf(stderr, "Failed to compile regex\n");
        return EXIT_FAILURE;
    }

    for (int i = optind; i < argc; i++) {
        grep_file(argv[i], &flags, &regex);
    }

    regfree(&regex);
    return 0;
}

void parse_flags(int argc, char *argv[], grep_flags *flags) {
    int opt;
    while ((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
        switch (opt) {
            case 'e':
                flags->e_flag = true;
                flags->pattern = optarg;
                break;
            case 'i':
                flags->i_flag = true;
                break;
            case 'v':
                flags->v_flag = true;
                break;
            case 'c':
                flags->c_flag = true;
                break;
            case 'l':
                flags->l_flag = true;
                break;
            case 'n':
                flags->n_flag = true;
                break;
            case 'h':
                flags->h_flag = true;
                break;
            case 's':
                flags->s_flag = true;
                break;
            case 'f':
                flags->f_flag = true;
                flags->pattern_file = optarg;
                break;
            case 'o':
                flags->o_flag = true;
                break;
            default:
                fprintf(stderr, "Usage: s21_grep [options] pattern [file...]\n");
                exit(EXIT_FAILURE);
        }
    }
}

void grep_file(const char *filename, grep_flags *flags, regex_t *regex) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        if (!flags->s_flag) {
            perror(filename);
        }
        return;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int match_count = 0;
    int line_number = 0;

    while ((read = getline(&line, &len, file)) != -1) {
        line_number++;
        int regex_result = regexec(regex, line, 0, NULL, 0);
        bool match = (regex_result == 0);

        if (flags->v_flag) match = !match;

        if (match) {
            if (flags->c_flag) {
                match_count++;
            } else {
                if (!flags->h_flag) printf("%s:", filename);
                if (flags->n_flag) printf("%d:", line_number);
                printf("%s", line);
            }
        }
    }

    if (flags->c_flag) {
        printf("%s:%d\n", filename, match_count);
    }
    if (flags->l_flag && match_count > 0) {
        printf("%s\n", filename);
    }

    free(line);
    fclose(file);
}