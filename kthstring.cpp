/*
К-я строка (kthstring.cpp)

Реализуйте структуру данных, которая поддерживает следующие операции:
* добавить в словарь строку S;
* найти в словаре k-ю строку в лексикографическом порядке.
Изначально словарь пуст.

Формат входных данных

Первая строка входного файла содержит число N — количество команд (1≤N≤10^5).
Последующие N строк содержат по одной команде каждая. Команды записываются следующим образом:
* 1 S — добавить строку S в словарь;
* 2 k — вывести k-ю строку в лексикографическом порядке.
Гарантируется, что при запросе 
k-й строки она существует. Также гарантируется, что сумма длин всех добавляемых строк не превышает 3*10^5.
Все строки состоят из строчных латинских букв.

Формат результата
Для каждого запроса второго типа выведите k-ю в лексикографическом порядке строчку из словаря на момент запроса. Гарантируется, что суммарная длина строк в выходном файле не превышает 10^5.

Примеры
7
1 pushkin
1 lermontov
1 tolstoy
1 gogol
1 gorkiy
2 5
2 1

tolstoy
gogol

*/

#include <map>
#include <iostream>

using namespace std;

struct Node{
    map<int, Node> next;
    bool terminal = false;
    long long counter = 0;
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    Node root;
    int n;
    cin >> n;
    for (; n > 0; --n) {
        int input;
        cin >> input;
        if (input != 1) {
            Node* current = &root;
            int K;
            cin >> K;
            {
                string result;
                while (K > 0) {
                    for (auto it = current->next.begin(); it != current->next.end(); ++it) {
                        if (K <= it->second.counter) {
                            current = &(it->second);
                            result += it->first;
                            if (current->terminal) --K;
                            break;
                        } else K = K - it->second.counter;
                    }
                }
                cout << result << '\n';
            }
            
            continue;
        }
        
        string str;
        cin >> str;
        Node* current = &root;
        for (char c : str){
            if (!current->next.contains(c))
                current->next[c] = *(new Node());
            current->counter++;
            current = &(current->next[c]);
        }
        
        current->counter += (!current->terminal);
        current->terminal = true;
    }
    return 0;
}