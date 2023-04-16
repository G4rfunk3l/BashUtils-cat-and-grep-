#ifndef SRC_GREP_MY_GREP_H_
#define SRC_GREP_MY_GREP_H_

#define MAX_BUF_SIZE 1024

#include <regex.h>

#include "../common/my_common.h"


struct grep_flags {
    int e; /* Шаблон. */
    int i; /* Игнорирует различия регистра. */
    int v; /* Инвертирует смысл поиска соответствий. */
    int c; /* Выводит только количество совпадающих строк. */
    int l; /* Выводит только совпадающие файлы. */
    int n; /* Предваряет каждую строку вывода номером строки из файла ввода. */
    int h; /* Выводит совпадающие строки, не предваряя их именами файлов. */
    int s; /* Подавляет сообщения об ошибках о несуществующих или нечитаемых файлах. */
    int f; /* file Получает регулярные выражения из файла. */
    int o; /* Печатает только совпадающие (непустые) части совпавшей строки. */
};

typedef struct Regex {
    char str_regex[MAX_BUF_SIZE][MAX_BUF_SIZE];
    int size;
} Regex;


void parse_flags(int argc, char **argv, struct grep_flags *flag, Regex *regex);
void my_grep(int argc, char **argv, struct grep_flags flag, Regex regex);
void print_file(FILE *file, char *filename, struct grep_flags flag, Regex regex);
void filename_to_prefix(char *prefix, char *filename, struct grep_flags flag, int check);
#ifdef __MACH__
void print_substring(char *sub_str, Regex regex, struct grep_flags flag);
#endif  // __MACH__
#ifdef __linux__
void print_substring(char *sub_str, char *regex, struct grep_flags flag, char *prefix);
#endif  // __linux__
void create_regex(char *str_regex, Regex regex);
int get_regex(char *sub_str, char *str_regex, struct grep_flags flag);
void set_regex(Regex *str_regex);

#endif  // SRC_GREP_MY_GREP_H_
