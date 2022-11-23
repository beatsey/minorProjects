/*
Требуется реализовать приоритетную очередь с помощью бинарной пирамиды, поддерживающую три операции: добавить элемент, извлечь максимальный элемент и удалить заданный элемент.
При просеивании нельзя совершать лишние перемещения (например, в случае равенства элементов).
Если при просеивании вниз, рассматриваемый элемент можно перемещать как влево вниз, так и вправо вниз, то следует выбрать лево.

Формат ввода
В первой строке вводятся два числа - максимальный размер приоритетной очереди N и количество запросов M, (1 <= M,N <= 10^5).
Далее идут M строк, в каждой строке - по одному запросу. Первое число в запросе задает его тип, остальные числа (если есть) - параметры запроса.
Тип 1 - извлечь максимальный (без параметров).
Тип 2 - добавить данный элемент в очередь. Запрос имеет один параметр - число из отрезка [-10^9;10^9].
Тип 3 - удалить элемент по индексу (индексы нумеруются с единицы).

Формат вывода
В ответ на запрос типа 1 следует вывести:
Если извлекать было нечего (очередь пуста), то -1.
Иначе - два числа, первое - индекс конечного положения элемента после его просеивания (если удален последний элемент и просеивать нечего, то вывести 0),
второе - значение извлеченного элемента.
В ответ на запрос типа 2 следует вывести: Если добавить нельзя (нет места, т.к. в очереди уже N элементов), то -1. Иначе - индекс добавленного элемента.
В ответ на запрос типа 3 следует вывести: Если элемента с таким индексом нет и удаление невозможно, то -1. Иначе - значение удаленного элемента.
После выполнения всех запросов требуется вывести пирамиду в её конечном состоянии.

*/

#include <iostream>

void swap(int& a, int& b) {
    int tmp = a;
    a = b;
    b = tmp;
}

int siftDown(int* a, int i, int size) {
    int left = 2 * i + 1;   // left — левый сын
    int right = 2 * i + 2;  // right — правый сын
    int larger;
    if (right < size && a[right] > a[left])
        larger = right;
    else {
        larger = left;
    }

    if(larger < size && a[larger] > a[i]) {
        swap(a[i], a[larger]);
        return siftDown(a, larger, size);
    }

    return i;
}

int siftUp(int* a, int i) {
    while (i > 0 && a[(i - 1) / 2] < a[i]) {
        swap(a[i], a[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
    return i;
}

int del(int* a, int i, int& size) {
    if (i >= size)
        return -1;

    size--;
    a[i] = a[size];

    // Один из этих вызовов ничего не делает
    int res = siftUp(a, i);
    if (res == i)
        res = siftDown(a, i, size);

    return res;
}

int extractMax(int* a, int& size, int& index) {
    if (size == 0)
        return -1000000001;

    int max = a[0];
    index = del(a, 0, size) + 1;
    if (size == 0) {
        index = 0;
    }
    return max;
}

int insert(int* a, int key, int& size, int maxSize) {
    if (size == maxSize)
        return -1;

    a[size] = key;
    int res = siftUp(a, size);
    size++;

    return res + 1;
}

int main() {
    int M, N;
    std::cin >> N >> M;
    int* A = new int[N];
    int size = 0;
    
    for (int i = 0; i < M; i++) {
        int type;
        std::cin >> type;
        if (type == 1) {
            int index;
            int max = extractMax(A, size, index);
            if (max == -1000000001)
                std::cout << -1 << std::endl;
            else {
                std::cout << index << ' ' << max << std::endl;
            }
        }
        else if (type == 2) {
            int k;
            std::cin >> k;
            std::cout << insert(A, k, size, N) << std::endl;
        }
        else if (type == 3) {
            int k;
            std::cin >> k;

            if(k <= 0 || k>size)
                std::cout << -1 << std::endl;
            else {
                std::cout << A[k - 1] << std::endl;
                del(A, k - 1, size);
            }
        }
    }

    for (int i = 0; i < size; i++) {
        std::cout << A[i] << ' ';
    }

    std::cout << std::endl;

    delete[] A;
    
    return 0;
}