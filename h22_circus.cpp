/*
Башня

В Бурляндск приехал цирк.Одним из привлекающих внимание горожан номеров всегда было построение как можно более высокой башни из группы циркачей.

В построенной башне один циркач стоит на земле, второй - на его плечах, третий - на плечах второго, и так далее.
У циркача под номером i вес равен wi, а сила — fi.
Сила — способность удерживать на себе заданный вес.
Точно известно, что более тяжёлый циркач является и более сильным.
Впрочем, циркачи с одинаковым весом могут иметь различную силу.
Формат входных данных

Первая строка ввода содержит 4<=N<=3000 — количество человек в команде, которые хотят построить башню.

Каждая их последующих строк содержит по два числа — вес и силу участника команды. Все числа — положительные целые, меньшие 10000.
Формат результата

Максимальная высота башни, которую может построить эта команда.
Примеры
Входные данные
4
1 9
5 13
13 15
16 20

Результат работы
4
*/

#include <iostream>
#include <vector>
#include <algorithm>

unsigned long long readULL() {
    char ch;
    while ((ch = getchar()) < '0' || ch > '9');
    unsigned long long result = ch - '0';

    while ((ch = getchar()) >= '0' && ch <= '9')
        result = result * 10 + ch - '0';

    return result;
}

int main()
{
    unsigned short N = readULL();
    int counter = 1;
    std::vector<unsigned long long> athlettes(N);

    /*
    std::vector<unsigned int> athlettes(N);

    for (int i = 0; i < N; i++) { // каким-то магическим образом при обратном цикле второй тест не проходится. Очень интересно
        std::cin >> athlettes[i].weight >> athlettes[i].strength;
    }

    std::sort(athlettes.begin(), athlettes.end());

    int currentWeight = athlettes[0].weight;

    for (int i = 1; i < N; i++) {
        if (athlettes[i].strength >= currentWeight) {
            currentWeight += athlettes[i].weight;
            counter++;
        }
    }
    */

    /* Стратегия с pair почему-то тоже не сработала, хотя она вроде полностью эквивалентна предыдущим со сдвигами
    std::vector<std::pair<int,int>> athlettes(N);
    int weight;
    int strength;

    for (int i = N - 1; i >= 0; i--) {
        std::cin >> weight >> strength;
        athlettes[i] = std::pair<int, int>(strength,weight); // (weight, strength)
    }

    std::sort(athlettes.begin(), athlettes.end(),comp);

    int currentWeight = athlettes[0].second;

    for (int i = 1; i < N; i++) {
        if (athlettes[i].first >= currentWeight) {
            currentWeight += athlettes[i].second;
            counter++;
        }
    }
    */

    /* Стратегии маленького-слабенького и слабенького-маленького дают ошибку на втором тесте, хотя и компактные

    std::vector<unsigned int> athlettes(N);
    
    // Стратегия маленького->слабенького
    for (int i=static_cast<int>(N)-1; i>=0;i--) {
        athlettes[i] = (static_cast<unsigned int>(readUShort()) << 16) + readUShort(); // weight + strength = 32 bit
    }
    std::sort(athlettes.begin(), athlettes.end());

    unsigned int currentWeight = athlettes[0]>>16;

    for (unsigned short i=1; i < N; i++) {
        if ((athlettes[i] & 0xFFFF) >= currentWeight) {
            currentWeight += athlettes[i] >> 16;
            counter++;
        }
    }
    */

    // Стратегия слабенького->маленького

    for (unsigned short i = 0; i < N; i++) {
        unsigned long long weight = readULL();
        if (weight > 10000)
            return -1;
        athlettes[i] = weight + (readULL() << 16); // strength + weight = 32 bit
    }

    std::sort(athlettes.begin(), athlettes.end());

    unsigned int currentWeight = athlettes[0] & 0xFFFF;

    for (unsigned short i = 1; i < N; i++) {
        if ((athlettes[i] >> 16) >= currentWeight) {
            currentWeight += athlettes[i] & 0xFFFF;
            counter++;
        }
    }

    std::cout << counter << std::endl;
    return 0;
}