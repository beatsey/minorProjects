#include <string.h>
#include <stdio.h>

void rstrip_newline(char *str) {
    while (*str != '\n' && *str != '\0') str++;
    *str = '\0';
}

int endswith(const char *ending, const char *source) {
    int len = 0, len2 = 0;
    while (*ending) { 
        ending++; 
        len++; 
    }
    while (*source) { 
        source++; 
        len2++; 
    }
    if (len2 < len) {
        return 0;
    }
    for(;len>0;len--;) {
        if (*--source != *--ending) {
            return 0;
        }
    }
    return 1;
}

int 
main(void) 
{
    char str1[82];
    char str2[82];
    fgets(str1, 82, stdin);
    fgets(str2, 82, stdin);
    rstrip_newline(str1);
    rstrip_newline(str2);
    if (endswith(str1, str2)) { // endswith(str1, str2) != 0
        printf("YES");
    } else {
        printf("NO");
    }
}
