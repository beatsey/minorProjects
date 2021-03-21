#include <iostream>

/*
Чуждые элементы

Последовательность из 2<=N<=1000000 элементов содержит натуральные числа от 1 до 10e18. Назовём пару соседних чисел, которая имеет общие множители, большие единицы, родственниками. В исходную последовательность вставляют натуральные числа (чуждые элементы) таким образом, что в итоговой последовательности не остаётся родственников. Требуется определить минимально возможную сумму чуждых элементов. Пример: в исходную последовательность

4 8 9 10
можно вставить чуждый элемент 5 после 4:

4 5 8 9 10
после чего последовательность не содержит родственников.

Формат входных данных
N
X1
X2
...
XN

Формат результата
Sum
*/

// 5 times faster than std::cin >> ULL
unsigned long long readNumFastest() {
    char ch;
    while ((ch = getchar()) < '0' || ch > '9');
    unsigned long long result = static_cast<unsigned long long>(ch - '0');

    while((ch = getchar()) >= '0' && ch <= '9')
        result = result * 10 + static_cast<unsigned long long>(ch - '0');

    return result;
}

int main()
{
    int N = readNumFastest(), sum = 0;
    unsigned long long lastM = readNumFastest(), M, tmp, x;

    for (; --N > 0;) {
        x = lastM;

        // read the number without calling the function
        char ch;
        while ((ch = getchar()) < '0' || ch > '9');
        M = static_cast<unsigned long long>(ch - '0');
        while ((ch = getchar()) >= '0' && ch <= '9')
            M = M * 10 + static_cast<unsigned long long>(ch - '0');

        lastM = M;

        // Наибольший общий множитель
        while ((tmp = x % M)) {
            x = M;
            M = tmp;
        }
        if (M != 1)
            sum++;
    }
    std::cout << sum << std::endl;

    return 0;
}