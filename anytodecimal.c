/*
В аргументах командной строки задаются 64-битные беззнаковые числа в 17-ричной системе счисления. На стандартный поток вывода напечатайте эти числа в десятичной системе счисления, упорядоченные по невозрастанию.

Пример запуска программы:
./solution 1 2 3
Результат работы программы:

3
2
1
*/

#include <stdio.h>
#include <stdlib.h>

unsigned long long getNumeric (char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    }else{
        return c - 'A' + 10;
    }
}

unsigned long long readULL(const char *s)
{
    char ch;
    int i = 0;
    while (!(((ch = s[i++]) >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'G')));
    
    unsigned long long result = getNumeric (ch);
    
    while (((ch = s[i++]) >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'G'))
    {
        result = result * 17 + getNumeric (ch);
    }

    return result;
}

int main (int argc, const char *argv[])
{
    if (argc == 1)
        return 0;
    
    unsigned long long *result = malloc ((argc - 1) * sizeof (unsigned long long));
    for (int i = 1; i < argc; i++) {
        result[i - 1] = readULL (argv[i]);
    }
    
    for (int i = 0; i < argc - 1; i++) {
        for (int j = i + 1; j < argc - 1; j++) {
            if (result[i] < result[j]) {
                unsigned long long tmp = result[i];
                result[i] = result[j];
                result[j] = tmp;
            }
        }
    }
    
    for (int i = 1; i < argc; i++) {
        printf ("%lld\n", result[i - 1]);
    }
    
    free (result);
    
    return 0;
}
