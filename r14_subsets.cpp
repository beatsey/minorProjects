/*
Подмножества
Множество задано строкой, то есть каждая буква есть элемент множества.
Но это множество — не совсем простое. Элементы в нём могут повторяться.
Два подмножества считаются одинаковыми, если все элементы одного множества совпадают с элементами другого. Например, множества, представленные строками abc и cba совпадают. Совпадают также множества abra и raba.
Ваша задача по заданной строке, представляющей исходное множество, вывести все различные его подмножества, каждое на отдельной строке вывода. Выводить можно в произвольном порядке. Выход не должен содержать совпадающие подмножества.
Пустое множество тоже является подмножеством исходного.

Input format
Исходное множество в виде строки

Output format
Все уникальные подмножества исходного множества по одному на строку. Подмножества не требуется как-либо упорядочивать, будет принят любой верный ответ.

Не забудьте, что пустая строка — тоже верное подмножество. В приведённом примере она следует первой, перед строкой a.

Examples
Input
abra

Output

a
b
ba
ar
rb
aa
raab
baa
abr
ara
r


Input
(empty)

Output
(empty line)

Input
Q1aQQ

Output
QQa
Qa
1
QQ
1a
QQQa
QQQ
1QQQ
a
1Q
1QQ

1QQQa
1QQa
Q
1Qa
*/
#include <iostream>
#include <string>

int main() {
    std::string input;
    std::getline(std::cin, input);

    if (input.length() == 0) {
        printf("\n");
        return 0;
    }

    int counter[26 * 2 + 10] = {};
    for(int i = input.length()-1;i>=0;i--){
        char c = input[i];
        if (c >= 'a' && c <= 'z')
            counter[c - 'a' + 10]++;
        else if (c >= 'A' && c <= 'Z')
            counter[c - 'A' + 10 + 26]++;
        else if (c >= '0' && c <='9')
            counter[c - '0']++;
    }

    char unique[24] = {}; // for unique characters
    int maxcounters[24] = {}; 
    int currentcounters[24] = {};
    int len = 0;
    for (int i = 0; i <10; i++) {
        if (counter[i]) {
            maxcounters[len] = counter[i];
            unique[len++] = '0' + (char)i;
        }
    }
    for (int i = 10; i < 10 + 26; i++) {
        if (counter[i]) {
            maxcounters[len] = counter[i];
            unique[len++] = 'a' + (char)(i - 10);
        }
    }
    for (int i = 10 + 26; i < 10 + 26 + 26; i++) {
        if (counter[i]) {
            maxcounters[len] = counter[i];
            unique[len++] = 'A' + (char)(i - 10 - 26);
        }
    }

    bool terminate = false;
    while (true) {
        for (int i = 0; i < len; i++) {
            for (int j = 0; j < currentcounters[i]; j++) {
                printf("%c", unique[i]);
            }
        }
        printf("\n");

        int ind = 0;

        while (currentcounters[ind]++ > maxcounters[ind]) {
            currentcounters[ind] = 0;
            if (ind++ == len) {
                terminate = true;
                break;
            }
        }
        if (terminate) break;
    }

    return 0;
}