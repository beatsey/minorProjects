﻿/*
Обратное число по модулю
Известно, что команда деления целых чисел на современных компьютерах исполняется неприлично долго. Оптимизирующие компиляторы во многих случаях заменяют операцию деления на константу группой операций, в которых имеется умножение на другую константу.

Для этого компилятору, в числе других действий, требуется найти такое число q для заданного делителя p, что q * p = 1 по известному модулю m.

Ваша задача по заданным числам 2 <= p,m <= 4 294 967 295 найти любое число q такое, чтобы (p * q) (mod m) = 1.

Известно также, что m — простое число, и что для заданных p и m ответ существует.

Формат входных данных
p m

Формат результата
q

Примеры
Входные данные
5 7

Результат работы
3

Входные данные
199212331 4010101141

Результат работы
525555399
*/

/*
Т.к. m простое, то можно было просто возвести число в степень m-1 и получить 1 :D
*/
#include <iostream>

int main()
{
    unsigned int p, m;
    std::cin >> p >> m;
    p = p % m;

    unsigned int num = p;

    unsigned long long q = 1;
    bool positive = true;
    while (num != 1) {
        unsigned int k = m / num,
            under = m - k * num,     // недобор
            upper = num - under;    // перебор

        if (upper <= under) {
            num = upper;
            q = q*(static_cast<unsigned long long>(k) + 1)%m;
        }
        else {
            num = under;
            q = q*k%m;
            positive = !positive;
        }
    }
    // positive==true -> p*q%m==1
    if (!positive) {
        // p*q%m==-1==m-1
        // p*(q*(p-1)+1)==1
        q = (q * (static_cast<unsigned long long>(p) - 1) + 1) % m;
    }
    std::cout << q << std::endl;
}