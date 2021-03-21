#include <iostream>
#include <string>
#include <type_traits>

/*
Последовательность строк
Последовательность строк формируется следующим образом:

Первая строка состоит из цифры 1.

Каждая из последующих строк формируется из номера строки, записанного в виде последовательности десятичных цифр, за которым дописана предыдущая строка и затем перевёрнутая предыдущая строка.

Вот несколько первых строк:

1
211
3211112
432111122111123
5432111122111123321111221111234
Заметьте, что десятая строка начнётся с символов 10, одиннадцатая — с символов 11 и так далее.

Ваша задача заключается в том, чтобы по заданному номеру строки и номеру её элемента вывести символ, стоящий в ней на указанном месте.

Формат входных данных
N M

P1 P2 ... PM

Ограничения:

1<=N<=30

1<=M<=100000

1<=Pi<=length(string).

Нумерация строк и символов в строках начинается с единицы.

Формат результата
M символов, не разделённых пробелами, соответствующие позициям Pi.

Примеры
Входные данные
5 5
2 4 6 8 10

Результат работы
42112
*/

template <char... symbols>
struct String {
    static constexpr char value[] = { symbols...,'\0' };
};

template <char... symbols>
constexpr char String<symbols...>::value[];

template <typename, typename>
struct Concat;

template <char... symbols1, char... symbols2>
struct Concat<String<symbols1...>, String<symbols2...>>
{
    using type = String<symbols1..., symbols2...>;
};

template <typename...>
struct Concatenate;

template <typename S, typename... Strings>
struct Concatenate<S, Strings...>
{
    using type = typename Concat<S, typename Concatenate<Strings...>::type>::type;
};

template <>
struct Concatenate<>
{
    using type = String<>;
};

template <std::size_t N>
struct NumberToStringReverse
{
    using type = typename Concat
        <
        String<'0' + N % 10>,
        typename std::conditional< (N >= 10), typename NumberToStringReverse<N / 10>::type, String<> >::type
        >::type;
};

template <>
struct NumberToStringReverse<0>
{
    using type = String<'0'>;
};


template <std::size_t N>
struct NumberToString
{
    using type = typename Concat
        <
        typename std::conditional< (N >= 10), typename NumberToString<N / 10>::type, String<> >::type,
        String<'0' + N % 10>
        >::type;
};

template <>
struct NumberToString<0>
{
    using type = String<'0'>;
};

template <std::size_t N>
struct GenStringReverse;


template <std::size_t N>
struct GenString {
    using type = typename Concatenate
        <
        typename NumberToString<N>::type,
        typename GenString<N - 1>::type,
        typename GenStringReverse<N - 1>::type
        >::type;
};

template <>
struct GenString<1>
{
    using type = String<'1'>;
};

template <std::size_t N>
struct GenStringReverse {
    using type = typename Concatenate
        <
        typename GenString<N - 1>::type,
        typename GenStringReverse<N - 1>::type,
        typename NumberToStringReverse<N>::type
        >::type;
};

template <>
struct GenStringReverse<1>
{
    using type = String<'1'>;
};

constexpr int maxval(int a, int b) {
    return a > b ?a:b;
}
// 20 - 1 mb
constexpr int NUMBER_OF_CACHED_STRS = 15;
constexpr const char* sequence = GenString<NUMBER_OF_CACHED_STRS>::type::value;

inline char getPthCharacter(int P, int n) {
    // Понижаем n тождественными преобразованиями к NUMBER_OF_CACHED_STRS
    while (n > maxval(NUMBER_OF_CACHED_STRS, 10)) { 
        if (P < ((1 << 9) + 1) << (n - 10)) { // ++
            if (P == 0)
                return '0' + n / 10;
            else if (P == 1)
                return '0' + n % 10;
            else
                P -= 2;
        } else {
            P = (((1 << 9) + 1) << (n - 9)) - 3 - P; // ++
        }
        n--;
    }

    if (NUMBER_OF_CACHED_STRS <= 9) {
        if (n == 10) {
            //f10_9
            if (P == 0) {
                return '1';
            }
            else if ((P - 1) >> 9 == 0) { // P лежит в первой половине девятой строки ++ проверить границу
                if (P == 1) {
                    return '0';
                }
                else {
                    P -= 2;
                }
            }
            else {
                P = (1 << 10) - 1 - P;
            }
            n = 9;
        }

        while (n > NUMBER_OF_CACHED_STRS) {
            // fk
            if ((P & (1 << (n - 1))) == 0) {
                if (P == 0) {
                    return '0' + n;
                }
                else {
                    P--;
                }
            }
            else {
                P = (1 << n) - P - 2;
            }
            n--;
        }
    }
    
    // n == NUMBER_OF_CACHED_STRS => просто считываем из строки
    return sequence[P];
}

int main()
{

    int N, M;
    std::cin >> N >> M;

    char* result = new char[M + 1];
    result[M] = '\0';

    // Если N <= NUMBER_OF_CACHED_STRS, то просто считываем символ
    // Сдвиг на начало нужной подстроки
    
    if (N <= NUMBER_OF_CACHED_STRS) { // ++++++
        int offset = NUMBER_OF_CACHED_STRS - N;
        if (N >= 10) // ++
            offset <<= 1; 
        else if(NUMBER_OF_CACHED_STRS>9) // ++
            offset = (NUMBER_OF_CACHED_STRS<<1) - N - 9;
        
        const char* pointer = &sequence[offset];
        // Получили нужную строку, просто считываем Pi
       
        for (int i = 0; i < M; i++) {
            int P;
            std::cin >> P;
            result[i] = pointer[P-1];
        }
    }
    else {
        for (int i = 0; i < M; i++) {
            int P;
            std::cin >> P;

            result[i] = getPthCharacter(P - 1, N);
        }
    }
    std::cout << result << std::endl;
    delete[] result;
	
	return 0;
}