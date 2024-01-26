#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// let all switches consist of CASES_COUNT cases and 1 default
enum
{
    CASES_COUNT = 2,
    SUB_C_LIMIT = 2,
};

// type hasn't changed
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
indexize_add(char *key)
{
    // if add_c is odd print add_c
    static unsigned long long add_c = 0;
    if (++add_c % 2 != 0) {
        printf("%lld\n", add_c);
    }
}

void
indexize_sub(char *key)
{
    // halt the function if reached SUB_C_LIMIT
    static unsigned long long sub_c = 0;
    if (++sub_c == SUB_C_LIMIT) {
        exit(0);
    }
}

int
main(int argc, char *argv[])
{
    Str_switch my_str_switch = {
        {
            {"add", indexize_add},
            {"sub", indexize_sub}
        },
        NULL
    };
    for (int i = 1; i < argc; ++i) {
        sw_implementation(&my_str_switch, argv[i]);
    }
    return 0;
}
