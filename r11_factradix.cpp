/*
Факториальная система счисления
Наряду с уже привычными позиционными системами счисления, к которым мы все уже привыкли, существует множество других, всё также позиционных, но с другими правилами вычисления весов позиций.
Мы рассмотрим факториальную систему счисления, в которой вес каждой позиции — факториал от её номера. Для позиций после десятичной точки используются обратные к факториалам веса.
Каждая правильная дробь (p < q) представляется в такой системе единственным конечным образом при условии, что в самом правом члене записи коэффициент отличен от нуля.
Ваша задача — найти такие числа ai < i, чтобы сумма их произведений на факториалы их индексов i равнялась заданной дроби.

Input format
1 <= P < Q < 1000

Output format
В одной строке через пробел выведите коэффициенты разложения, начиная с a2.

Гарантируется, что число выводимых членов будет меньше 1000.

Examples
Input
1 4

Output
0 1 2

Input
5 7

Output
1 1 1 0 4 2
*/

#include <iostream>

constexpr void strCpyFast(char*& dest, const char* source) {
    while ((*dest = *source++))dest++;
}
constexpr char* uintToString(unsigned int x, char* bufferEnd) {
    if (x == 0)
        *--bufferEnd = '0';
    else
        while (x) {
            *--bufferEnd = '0' + x % 10;
            x /= 10;
        }
    return bufferEnd;
}

int main()
{
    unsigned int P, Q;
    std::cin >> P >> Q;
    char output[1000 * 5] = {}; // Верхняя оценка размера вывода
    char* buffer_end = output;

    for (unsigned int i = 2; P && i < 1002; i++) {
        P *= i;
        *buffer_end++ = ' ';
        strCpyFast(buffer_end, uintToString(P / Q, output + 1000 * 5-1));
        P %= Q;
    }
    std::cout << (output +1) << std::endl;

    return 0;
}