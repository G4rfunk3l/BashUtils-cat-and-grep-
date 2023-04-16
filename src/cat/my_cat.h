#ifndef SRC_CAT_MY_CAT_H_
#define SRC_CAT_MY_CAT_H_

#include "../common/my_common.h"


struct cat_flags {
    int b;
    int e;
    int n;
    int s;
    int t;
    int v;
};

void parse_flags(int argc, char **argv, struct cat_flags *flag);
void my_cat(int argc, char **argv, struct cat_flags flag);
void b_n_flag_handling(char sub_str, int *line, struct cat_flags flag);
void t_v_flag_handling(char sub_char, struct cat_flags flag);
int s_flag_handling(char sub_str, int *squeeze, struct cat_flags flag);
void v_flag_handling(char *sub_str);
int is_control_sym(char ch);
#ifdef __linux__
int my_strchr(const char *sub_str, size_t size, char ch);
#endif  // __linux__



#endif  // SRC_CAT_MY_CAT_H_
