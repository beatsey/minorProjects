#include <iostream>
#include <set>

/*
Количество подстрок

Назовём подстрокой любой набор подряд идущих символов строки. Например, в строке aba можно найти три подстроки длины один: a, b, a, две подстроки длины два: ab и ba, а также одну подстроку длины 3: aba.
Две подстроки здесь совпадают, поэтому различных подстрок здесь 5.
Нужно для заданной строки, состоящей из строчных букв латинского алфавита, определить, сколько в ней можно найти различных подстрок.

Формат входных данных
Строка, длиной от 5 до 10000 символов.

Формат результата
Количество различных подстрок в данной строке.

Примеры
Входные данные
abracadabra

Результат работы
54
*/

constexpr const char * removeSuffix(const char * less,const char * more) {
    while (*less == *more++)less++;
    return less;
}
struct constCharFastComparator_class {
    constexpr bool operator()(const char* a, const char* b) const
    {
        while (*a == *b && (*a)) {
            a++;
            b++;
        }
        return *a < *b;
    }
};
using myMultiset = std::multiset<const char*, constCharFastComparator_class>;
int main()
{
    char input[10001] = {};
    std::cin >> input;

    myMultiset substrings; // should be faster than set
    const char* pointer = input;
    for (;*pointer;pointer++) {
        myMultiset::iterator lower_bound = substrings.lower_bound(pointer); // known substrings are always longer than current one
        if ((lower_bound == substrings.end()) || (*removeSuffix(pointer, *lower_bound)))
            substrings.insert(pointer);
    }

    unsigned int counter = pointer - *substrings.begin(); // task says we have atleast 2 symbols input so this wouldn't be a problem
    for (myMultiset::iterator it_now = substrings.begin(), it_last = it_now++; it_now != substrings.end(); it_last = it_now++)
        counter += pointer - removeSuffix(*it_now, *it_last); // it_last always less than it_now in lexicographical order (a<aa<b<c<..<z)

    std::cout << counter << std::endl;
    return 0;
}