﻿/*
Problem 04-11: Экстерминатус
Мир наш исполнен войны - целая вечность сражений во имя Императора. Он никогда не прекращает и не отступается от бесконечной вражды, а значит - не должны и мы.

Второй год Похода Мучений. В отдалённой системе войска Императора столкнулись с планетой полной ужасающих человекоподобных зверей, представляющих собой серьёзную угрозу. После ожесточённых боёв связь с ударным отрядом чёрных тамплиеров во главе с братом Герхартом была потеряна, в связи с чем было приятно единственно верное решение в таких ситуациях - ЭКСТЕРМИНАТУС, то есть полное уничтожение всего живого на поверхности. Для запуска орбитальной бомбардировки требуются специальные коды запуска. Обычно они приходят на отдельный канал и с ними не возникает никаких проблем, но в этот раз в связи с оплошностью подчинённого несколько передач принимались по одному каналу и результаты перемешались. Ваша задача состоит в том, чтобы извлечь из полученной информации коды запуска орудий.

Передача состоит из заглавных и строчных латинских букв, цифр, а также 4 основных арифметических действий '+', '-', '*', '/'. Её длина не превосходит 2000 символов. Известно, что кодом является некоторая команда вида A op B, где A и B - целые неотрицательные числа, а op - одно из арифметических действий, результат которой является корректно вычислимым выражением модуль которого не превосходит 120000. При этом выражение "A op B" является подстрокой исходного сообшения. Гарантируется, что числа A,B и результат операции над ними не переполняют 32-х битные целые знаковые числа. Необходимо найти все такие команды и вывести их каждую с новой строки в виде A op B = res, где res - результат вычисления. Всё остальное считается мусором из других передач. Заметим, что для выражения A op1 B op2 C нужно вывести
A op1 B = res1
B op2 C = res2
Examples
Input
rDU+9519+28006-+45350-80003-7034/14870/50385i-25266-39120*8557
Output
9519 + 28006 = 37525
45350 - 80003 = -34653
80003 - 7034 = 72969
7034 / 14870 = 0
14870 / 50385 = 0
25266 - 39120 = -13854
*/

#include <stdio.h>

int main(void)
{
    char str[2001];
    scanf("%s", str);

    int number_tmp = 0; // переменная для сохранения текущего числа

    int numbers[2]; // массив, хранящий два числа - аргумента
    int numbersLen = 0; // длина массива

    char op = 0; // операция +, -, /, *
    int previousIsDigit = 0; // флаг, показывающий, что до текущего символа было число

    char c;
    int i = 0; // индекс текущего элемента в строке
    do {
        c = str[i++];

        if ((c >= '0') && (c <= '9')) {
            number_tmp = number_tmp * 10 + c - '0'; 
            previousIsDigit = 1;
        }
        else {
            if (previousIsDigit) { // прочитали число
                numbers[numbersLen++] = number_tmp; // добавляем к аргументам число

                if (numbersLen == 2) { // совершаем операцию
                    int result;
                    int bad = 0; // флаг плохой операции (если делим на 0 или операция не + - / *)
                    switch (op) {
                    case '-':
                        result = numbers[0] - numbers[1];
                        break;
                    case '+':
                        result = numbers[0] + numbers[1];
                        break;
                    case '*':
                        result = numbers[0] * numbers[1];
                        break;
                    case '/':
                        if (numbers[1] == 0)
                            bad = 1;
                        else
                            result = numbers[0] / numbers[1];
                        
                        break;
                    default:
                        bad = 1;
                        break;
                    }

                    // вывод результата
                    if ((bad == 0) && ((result<=120000) && (result>=-120000))) // ... вычислимым выражением модуль которого не превосходит 120000
                        printf("%d %c %d = %d\n", numbers[0], op, numbers[1], result);

                    numbers[0] = numbers[1];
                    numbersLen = 1;
                }

                if (((c == '-') || (c == '+') || (c == '*') || (c == '/'))) { // запоминаем операцию, если мы её встретили
                    op = c;
                }
                else { // это не цифра и не операция
                    op = 0; // никаких операций не встречали
                    numbersLen = 0; // никаких аргументов не встречали
                }
            }
            else { // встретилось два символа не цифры подряд
                numbersLen = 0;
                op = 0;
            }

            number_tmp = 0; // обнуляем текущее число
            previousIsDigit = 0; // отмечаем, что последний символ был не цифрой
        }

    } while (c != 0);
}