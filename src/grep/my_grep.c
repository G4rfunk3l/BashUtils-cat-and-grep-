#include "my_grep.h"

int main(int argc, char **argv) {
    errno = 0;
    struct grep_flags flag = {0};
    if (argc > 2) {
        Regex regex = {0};

        parse_flags(argc, argv, &flag, &regex);
        my_grep(argc, argv, flag, regex);
    } else {
        errno = 1;
        if (!flag.s) {
            fprintf(stderr, "Usage: my_grep [OPTION]... PATTERNS [FILE]...");
        }
    }

    return errno;
}

void parse_flags(int argc, char **argv, struct grep_flags *flag, Regex *regex) {
    /* функция парсинга флагов, принимает количество передаваемых элементов argc, массив с текстом из файлов argv,
    регулярку regex для паттерна, в зависимости от переданных флагов включает условия для обработки текста по этим флагам */

    int option = 0;
    int optindex = 0;
    struct option options[] = {0};

    while ((option = getopt_long(argc, argv, "e:ivclnhsf:o", options, &optindex)) != -1) {
        switch (option) {
            case 'e':
                strcat(regex->str_regex[regex->size++], optarg);
                flag->e = 1;
                break;
            case 'i':
                flag->i = 1;
                break;
            case 'v':
                flag->v = 1;
                break;
            case 'c':
                flag->c = 1;
                break;
            case 'l':
                flag->l = 1;
                break;
            case 'n':
                flag->n = 1;
                break;
            case 'h':
                flag->h = 1;
                break;
            case 's':
                flag->s = 1;
                break;
            case 'f':
                strcat(regex->str_regex[regex->size], optarg);
                set_regex(regex);
                flag->f = 1;
                break;
            case 'o':
                flag->o = 1;
                break;
            default:
                break;
        }
    }
}

void my_grep(int argc, char **argv, struct grep_flags flag, Regex regex) {
    /* основная функция grep - принимает указатель на количество элементов argc, массив с текстом из файлов argv и
    регулярку с паттерном (при флагах e или f) либо для паттерна, производит поиск в файле по паттерну и
    выводит совпадения в stdout (функция print_file) */

    if (!(flag.e || flag.f)) {
        strcat(regex.str_regex[regex.size++], argv[optind++]);
    }
    FILE *fptr = NULL;
    if (optind + 1 == argc) {
        flag.h = 1;
        }
    if (optind < argc) {
        for (int i = optind; i < argc; i++) {
            if (!(fptr = fopen(argv[i], "r"))) {
                if (!flag.s) {
                    fprintf(stderr, "my_grep: %s: No such file or directory\n", argv[i]);
                    errno = 2;
                }
            } else {
                print_file(fptr, argv[i], flag, regex);
            }
            if (fptr) {
                fclose(fptr);
            }
        }
    } else {
        if (!flag.s) {
            errno = 2;
            fprintf(stderr, "Usage: grep [OPTION]... PATTERNS [FILE]...");
        }
    }
}

void print_file(FILE* fptr, char *filename, struct grep_flags flag, Regex regex) {
    /* функция принта в stdout - принимает указатели на файл и на его название, массив флагов и регулярку с паттерном;
    strs - количество строк с совпадениями, lines - количество строк в файлах */

    #ifdef __MACH__
    size_t strs = 0;
    size_t lines = 0;
    size_t size = 0;
    char *sub_str = NULL;
    char prefix[MAX_BUF_SIZE] = {0};
    char str_regex[MAX_BUF_SIZE] = {0};

    create_regex(str_regex, regex);
    while (getline(&sub_str, &size, fptr) != -1) {
        lines++;
        if ((flag.v && get_regex(sub_str, str_regex, flag)) ||
            (!flag.v && !get_regex(sub_str, str_regex, flag))) {
            if (flag.c || flag.l) {
                strs++;
            } else {
                filename_to_prefix(prefix, filename, flag, 1);
                if (flag.n) {
                    char buffer[MAX_BUF_SIZE] = {0};

                    sprintf(buffer, "%lu:", (unsigned long)lines);
                    strcat(prefix, buffer);
                }
                printf("%s", prefix);
                if (flag.o && !flag.v) {
                    print_substring(sub_str, regex, flag);
                } else {
                    printf("%s", sub_str);
                    if (!strchr(sub_str, '\n')) {
                        printf("\n");
                    }
                }
            }
            if (flag.l) {
                break;
            }
        }
        memset(prefix, 0, MAX_BUF_SIZE);
    }
    free(sub_str);
    filename_to_prefix(prefix, filename, flag, 0);
    if (flag.c) {
        if (!flag.h) {
            printf("%s:", prefix);
        }
        printf("%lu\n", (unsigned long)strs);
    }
    if (flag.l) {
        if (strs) {
            printf("%s\n", prefix);
        }
    }
    #endif  // __MACH__
    #ifdef __linux__
    size_t strs = 0;
    size_t lines = 0;
    size_t size = 0;
    char *sub_str = NULL;
    char prefix[MAX_BUF_SIZE] = {0};
    char str_regex[MAX_BUF_SIZE] = {0};

    create_regex(str_regex, regex);
    while (getline(&sub_str, &size, fptr) != -1) {
        lines++;
        if ((flag.v && get_regex(sub_str, str_regex, flag)) ||
            (!flag.v && !get_regex(sub_str, str_regex, flag))) {
            if (flag.c || flag.l) {
                (strs++);
            } else {
                if (!(flag.o && flag.v)) {
                    filename_to_prefix(prefix, filename, flag, 1);
                    if (!flag.o) {
                        printf("%s", prefix);
                    }
                    if (flag.n) {
                        if (flag.o) {
                            char buffer[MAX_BUF_SIZE] = {0};

                            sprintf(buffer, "%lu:", (unsigned long)lines);
                            strcat(prefix, buffer);
                        } else {
                            printf("%lu:", (unsigned long)lines);
                        }
                    }
                }
                if (flag.o) {
                    print_substring(sub_str, str_regex, flag, prefix);
                } else {
                    printf("%s", sub_str);
                    if (!strchr(sub_str, '\n')) {
                        printf("\n");
                    }
                }
            }
            if (flag.l) {
                break;
            }
        }
        memset(prefix, 0, MAX_BUF_SIZE);
    }
    free(sub_str);
    if (flag.l) {
        if (strs) {
            filename_to_prefix(prefix, filename, flag, 0);
            printf("%s", prefix);
        }
    } else if (flag.c) {
        filename_to_prefix(prefix, filename, flag, 1);
        printf("%s", prefix);
        printf("%lu\n", (unsigned long)strs);
    }
    #endif  // __linux__
    return;
}

void filename_to_prefix(char *prefix, char *filename, struct grep_flags flag, int check) {
    /* вспомогательная функция принта, принимает указатель на массив prefix, массив с названием файла,
    стракт с флагами, копирует в массив prefix название файла, в зависимости от места вызова и флагов
    (check) добавляет :, в линуксе также принтует filename */

    if (!flag.h || flag.l) {
        #ifdef __MACH__
        strcat(prefix, filename);
        if (check) {
            strcat(prefix, ":");
        }
        #endif  // __MACH__
        #ifdef __linux__
        if (check) {
            strcat(prefix, filename);
            strcat(prefix, ":");
        } else {
            printf("%s\n", filename);
        }
        #endif  // __linux__
    }
}

#ifdef __MACH__
void print_substring(char *sub_str, Regex regex, struct grep_flags flag) {
    /* вспомогательная функция принта, принимает указатель на строку, регулярку
    и состояние флагов, принтует эту строку (sub_str) */

    for (int i = 0; i < regex.size; i++) {
        regex_t struct_regex = {0};
        regmatch_t rm = {0};
        int reg = REG_EXTENDED;

        if (flag.i) {
            reg = REG_ICASE;
        }
        if (strlen(regex.str_regex[i]) && !regcomp(&struct_regex, regex.str_regex[i], reg)) {
            while ((regexec(&struct_regex, sub_str, 1, &rm, 0)) != REG_NOMATCH) {
                printf("%.*s\n", (int)(rm.rm_eo - rm.rm_so), sub_str + rm.rm_so);
                sub_str += rm.rm_eo;
            }
        }
        regfree(&struct_regex);
    }
}
#endif  // __MACH__

#ifdef __linux__
void print_substring(char *sub_str, char *regex, struct grep_flags flag, char *prefix) {
    /* вспомогательная функция принта, принимает указатель на строку, регулярку,
    состояние флагов и строку prefix, содержащую название файла, принтует эту строку (sub_str) */

    regex_t struct_regex = {0};
    regmatch_t rm = {0};
    int reg = REG_EXTENDED;

    if (flag.i) {
        reg = REG_ICASE;
    }
    if (strlen(regex) && !regcomp(&struct_regex, regex, reg)) {
        while ((regexec(&struct_regex, sub_str, 1, &rm, 0)) != REG_NOMATCH) {
            printf("%s", prefix);
            printf("%.*s\n", (int)(rm.rm_eo - rm.rm_so), sub_str + rm.rm_so);
            sub_str += rm.rm_eo;
        }
    }
    regfree(&struct_regex);
}
#endif  // __linux__

void create_regex(char *str_regex, Regex regex) {
    /* функция принимает указатель на регулярку с паттерном и указатель на пустой массив
    str_regex для записи паттерна, копирует массив с паттерном str_regex из регулярки в этот массив,
    ставит | между каждым элементом массива */

    for (int i = 0; i < regex.size; i++) {
        if (!regex.str_regex[i]) {
            continue;
        }
        if (i == 0) {
            strcat(str_regex, regex.str_regex[i]);
        } else {
            strcat(str_regex, "|");
            strcat(str_regex, regex.str_regex[i]);
        }
    }
}

int get_regex(char *sub_str, char *str_regex, struct grep_flags flag) {
    /* функция принимает указатель на обратабываемую строку, указатель на строку с записанным паттерном и
    состояние флагов и проводит сравнение строки с паттерном, в случае нахождения совпадений
    обрабатывает и возвращает совпавшую строку, иначе возвращает REG_NOMATCH */

    regex_t struct_regex = {0};
    int res = 0;
    int reg = REG_EXTENDED;

    if (flag.i) {
        reg = REG_ICASE;
    }
    if (strlen(str_regex) && !regcomp(&struct_regex, str_regex, reg)) {
        res = regexec(&struct_regex, sub_str, 0, NULL, 0);
    } else {
        res = REG_NOMATCH;
    }
    regfree(&struct_regex);

    return res;
}

void set_regex(Regex *regex) {
    /* функция устанавливает в качестве паттерна указанный файл (при флаге f),
    принимает указатель на регулярку для паттерна и стракт с флагами, записывает в
    массив регулярки str_regex паттерн из файла */

    FILE *fptr = NULL;
    if (!(fptr = fopen(regex->str_regex[regex->size], "r"))) {
            fprintf(stderr, "my_grep: %s: No such file or directory\n",
                    regex->str_regex[regex->size]);
            errno = 2;
        memset(regex->str_regex[regex->size], 0, MAX_BUF_SIZE);
    } else {
        memset(regex->str_regex[regex->size], 0, MAX_BUF_SIZE);
        char *buffer = NULL;
        size_t size = 0;
        while (getline(&buffer, &size, fptr) != -1) {
            size_t str_len = strlen(buffer);
            if (buffer[str_len - 1] == '\n') {
                buffer[str_len - 1] = '\0';
            }
            if (str_len) {
                strcat(regex->str_regex[regex->size++], buffer);
            }
        }
        free(buffer);
    }
    if (fptr) {
        fclose(fptr);
    }
    return;
}
