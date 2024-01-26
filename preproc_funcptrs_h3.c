#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

// let all switches consist of CASES_COUNT cases and 1 default
enum
{
    CASES_COUNT = 2,
};

typedef struct {
    char *str;
    void (*func)(char *);
} Case;

typedef struct {
    Case body[CASES_COUNT];
    void (*default_func)(char *);
} Str_switch;

void
sw_implementation(Str_switch *code, char *key)
{
    for (int i = 0; i < CASES_COUNT; ++i) {
        if (strcmp(code->body[i].str, key) == 0) {
            if (code->body[i].func != NULL) {
                // function code isn't empty
                code->body[i].func(key);
            }
            return;
        }
    }
    // if algo haven't stopped, trigger default_func
    if (code->default_func != NULL) {
        // function code isn't empty
        code->default_func(key);
    }
}

void
to_uppercase(char *str)
{
    char *p = str;
    while (*p) {
        printf("%c", toupper((unsigned char) *p++)); // cus char may be signed (EOF etc.)
    }
    printf("\n");
}

void
is_decimal_num(char *str)
{
    // base case
    if (strcmp(str, "0") == 0) {
        printf("NUMBER\n");
        return;
    }
    char *end = NULL;
    long num = strtol(str, &end, 10);
    if (num != (int) num) {
        // can't store in int
        printf("UNKNOWN\n");
        return;
    }
    if (num == LONG_MAX || num == LONG_MIN || num == 0) {
        // there is an error
        printf("UNKNOWN\n");
        return;
    }
    if ((!isdigit(*str) && *str != '-') || *end) {
        // there is some symbols before our number or after our number
        // ex. 1234i -> *end == i
        printf("UNKNOWN\n");
        return;
    }
    // all good
    printf("NUMBER\n");
}

int
main(int argc, char *argv[])
{
    Str_switch my_str_switch = {
        {
            {"add", to_uppercase},
            {"sub", to_uppercase}
        },
        is_decimal_num
    };
    for (int i = 1; i < argc; ++i) {
        sw_implementation(&my_str_switch, argv[i]);
    }
    return 0;
}