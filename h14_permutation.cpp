/*
Перестановки
Как известно, из множества из N различных предметов можно сделать N! различных перестановок.

Если предметы можно сравнивать между собой, то перестановки можно перенумеровать в лексикографическом порядке. Например, перестановки множества {1,2,3} будут идти в следующем порядке: {1,2,3}, {1,3,2}, {2,1,3}, {2,3,1}, {3,1,2}, {3,2,1}.

Таким образом, все перестановки множества различных элементов можно пронумеровать от 1 до N!.

В нашей задаче мы будем переставлять элементы из множества натуральных чисел от 1 до N.

Формат входных данных
На вход программы подаётся два числа — количество предметов в перестановке 2<=N<=20 и номер перестановки 1<=M<=2*10e18.

Формат результата
Вывести через пробел элементы перестановки, имеющей номер M.

Примеры
Входные данные
5
120

Результат работы
5 4 3 2 1

Входные данные
10
73238

Результат работы
1 3 9 6 8 4 7 2 10 5
*/

#include <iostream>
#include <vector>

constexpr unsigned long long factorial(unsigned int N) {
    unsigned long long f = 1;
    for (int i = N; i > 1; i--) {
        f *= i;
    }
    return f;
}

constexpr unsigned long long factorial_table[20] = {
    factorial(1),
    factorial(2),
    factorial(3),
    factorial(4),
    factorial(5),
    factorial(6),
    factorial(7),
    factorial(8),
    factorial(9),
    factorial(10),
    factorial(11),
    factorial(12),
    factorial(13),
    factorial(14),
    factorial(15),
    factorial(16),
    factorial(17),
    factorial(18),
    factorial(19),
    factorial(20)
};

int main()
{
    std::vector<int> tokens = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};

    int N; // number of elements
    unsigned long long permutation;
    std::cin >> N >> permutation;

    tokens.resize(N);
    permutation = (permutation - 1) % factorial_table[--N];

    while (N-- > 0) {
        int index = permutation / factorial_table[N];
        permutation %= factorial_table[N];

        std::cout << tokens[index] << ' ';
        tokens.erase(tokens.begin() + index);
    }

    std::cout << tokens[0] << std::endl;

    return 0;
}