#include "my_cat.h"

int main(int argc, char **argv) {
    errno = 0;

    if (argc > 1) {
        struct cat_flags flag = {0};

        parse_flags(argc, argv, &flag);
        my_cat(argc, argv, flag);
    } else {
        fprintf(stderr, "usage: my_cat [OPTION]... [FILE]...");
        errno = 1;
    }
    return errno;
}

void parse_flags(int argc, char **argv, struct cat_flags *flag) {
    /* Функция парсинга флагов, принимает количество передаваемых элементов argc, массив с текстом из файлов argv,
    в зависимости от переданных флагов включает условия для обработки текста по этим флагам */

    int opt = 0;
    int optindex = 0;
    struct option options[] = {
        {"number-nonblank", no_argument, 0, 'b'},
        {"number", no_argument, 0, 'n'},
        {"squeeze-blank", no_argument, 0, 's'},
        {0, 0, 0, 0}};

    while ((opt = getopt_long(argc, argv, "benstvET", options, &optindex)) != -1) {
        switch (opt) {
            break;
        case 'b':
            flag->b = 1;
            break;
        case 'e':
            flag->e = 1;
            flag->v = 1;
            break;
        case 'n':
            flag->n = 1;
            break;
        case 's':
            flag->s = 1;
            break;
        case 't':
            flag->t = 1;
            flag->v = 1;
            break;
        case 'v':
            flag->v = 1;
            break;
        case 'E':
            flag->e = 1;
            break;
        case 'T':
            flag->t = 1;
        default:
            break;
        }
    }
}

void my_cat(int argc, char **argv, struct cat_flags flag) {
    /* основная функция cat - принимает указатель на количество элементов argc и массив с текстом из файлов argv,
    производит обработку текста по флагам и принтует в stdout */

    FILE *fptr = NULL;
    int lines = 1;
    #ifdef __linux__
    int no_slash_n = 0;
    #endif  // __linux__

    for (int i = optind; i < argc; i++) {
        if (!(fptr = fopen(argv[i], "r"))) {
            fprintf(stderr, "my_cat: %s: No such file or directory\n", argv[i]);
            errno = 2;
        } else {
            char *sub_str = NULL;
            size_t size = 0;
            int squeeze = 0;

            while ((int)(size = getline(&sub_str, &size, fptr)) != -1) {
                if (s_flag_handling(*sub_str, &squeeze, flag)) {
                    continue;
                }
                #ifdef __MACH__
                if (flag.b || flag.n) {
                    b_n_flag_handling(*sub_str, &lines, flag);
                }
                #endif  // __MACH__
                #ifdef __linux__
                if (!no_slash_n && (flag.b || flag.n)) {
                    b_n_flag_handling(*sub_str, &lines, flag);
                }
                no_slash_n = !my_strchr(sub_str, size, '\n');
                #endif  // __linux__
                for (size_t j = 0; j < size; j++) {
                    if (flag.e && sub_str[j] == '\n') {
                        printf("$");
                    }
                    if (flag.t || flag.v) {
                        t_v_flag_handling(sub_str[j], flag);
                    } else {
                        printf("%c", sub_str[j]);
                    }
                }
            }
            free(sub_str);
        }
#ifdef __MACH__
        lines = 1;
#endif   // __MACH__

        if (fptr) {
            fclose(fptr);
        }
    }
}

void b_n_flag_handling(char sub_str, int *lines, struct cat_flags flag) {
    /* Функция обработки флагов -b и -n. Принимает указатель на текущую строку,
    нумерует (для -b только непустые) строки */

    if ((flag.n && !flag.b) || (flag.b && sub_str != '\n')) {
        printf("%6d\t", *lines);
        *lines += 1;
    }
}

void t_v_flag_handling(char sub_char, struct cat_flags flag) {
    /* Функция обработки флагов -t и -v. Принимает указатель на текущий обрабатываемый символ,
    отображает табы как ^I и другие управляющие символы по аналогии */

    if (flag.t && sub_char == '\t') {
        printf("^I");
    } else if (flag.v && is_control_sym(sub_char)) {
        char sym;
        if (sub_char == 127) {
            sym = '?';
        } else {
            sym = '@' + sub_char;
        }
        printf("^%c", sym);
    } else {
        printf("%c", sub_char);
    }
}

int s_flag_handling(char sub_str, int *squeeze, struct cat_flags flag) {
    /* Функция обработки флага -s. Принимает указатель на текущую строку,
    сжимает несколько пустых строк подряд в одну */

    int res = 0;

    if (flag.s && sub_str == '\n') {
        if (!*squeeze) {
            *squeeze = 1;
        } else {
            res = 1;
        }
    } else {
        *squeeze = 0;
    }
    return res;
}

int is_control_sym(char ch) {
    /* Функция проверки символа на его вхождение в ряд
    служебных, кроме tab и enter. Принимает символ и возвращает 1, если он
    служебный и 0, если нет */

    int is_control_sym = 0;

    if ((ch >= 0 && ch != 9 && ch != 10 && ch <= 31) || ch == 127) {
        is_control_sym = 1;
    }

    return is_control_sym;
}

#ifdef __linux__
int my_strchr(const char *sub_str, size_t size, char ch) {
    int res = 0;
    for (size_t i = 0; i < size; i++) {
        if (sub_str[i] == ch) {
            res = 1;
            break;
        }
    }

    return res;
}
#endif  // __linux__
