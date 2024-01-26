/*pointers.cpp

Реализовать функцию my_strcat конкатенации двух строк (аналог функции strcat). Нельзя использовать операцию индексации (квадратные скобки) и ее эквивалентные выражения (т.е. требуется эффективная реализация). Эта функция не должна знать, как получены строки (все ненулевые символы считаются значимыми!).

Для тестирования этой функции напишите функцию main. Она считывает две строки (используйте функцию fgets). Длина каждой строки не превосходит 80 символов. Не забудьте заменить символ перевода строки на ноль! Затем вызывается целевая функция так, чтобы в конец первой строки добавилась вторая строка. В конце печатается строка-результат. Функция main завершается явным return 0.

Примеры
abc
def

abcdef
*/

#include <string.h>
#include <stdio.h>

void rstrip_newline(char * str) {
    while(*str != '\n' && *str != '\0') str++;
    *str = '\0';
}

void my_strcat(char * destination, const char * source) {
    while(*destination) destination++;
    while(*destination = *source++) destination++;
}

int main(){
    char str1[162];
    char str2[82];
    fgets(str1, 82, stdin);
    fgets(str2, 82, stdin);
    
    rstrip_newline(str1);
    rstrip_newline(str2);
    
    my_strcat(str1, str2);
    printf("%s",str1);
}