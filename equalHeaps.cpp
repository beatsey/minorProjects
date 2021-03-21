#include <iostream>
#include <vector>

/*
Две кучи
Имеется 2<=N<=23 камня с целочисленными весами W1, W2, ... , WN. Требуется разложить их на две кучи таким образом, чтобы разница в весе куч была минимальной. Каждый камень должен принадлежать ровно одной куче.

Формат входных данных
N
W1 W2 ... WN

Формат результата
Минимальная неотрицательная разница в весе куч.

Примеры
Входные данные
5
8 9 6 9 8

Результат работы
4

Входные данные
6
14 2 12 9 9 8

Результат работы
2
*/

template <class T>
class BackpackSolver {

    // Размер рюкзака
    T bagSize;

    // Массив предметов
    std::vector<T> items;

    size_t getMaxCommonFactor(size_t x, size_t y) {
        size_t tmp;

        while ((tmp = x % y)) {
            x = y;
            y = tmp;
        }

        return y;
    }

    // Кратно уменьшаем размерность задачи, поделив на НОД всех масс и размера рюкзака
    T reduceMasses() {
        if (bagSize == 0 || items.size() == 0) return 1;

        size_t MCF = bagSize;
        for (size_t i = 0, n = items.size(); i < n; i++) {
            MCF = getMaxCommonFactor(items[i], MCF);
            if (MCF <= 1) return 1;
        }

        bagSize /= MCF;
        for (size_t i = 0, n = items.size(); i < n; i++) {
            items[i] /= MCF;
        }

        return MCF;
    }
public:
    BackpackSolver() :bagSize(0) {}
    BackpackSolver(T bagSize, std::vector<T>& items) :bagSize(bagSize),items(items) {}
    T solve() {

        // Множитель для сокращения масс предметов и рюкзака
        reduceMasses();

        // Все N предметов находятся в items
        std::vector<T> activeRow(bagSize + 1, 0);

        for (size_t i = 0, N = items.size(); i < N; i++) {
            T j;
            for (j = bagSize; j > items[i]; --j) {
                const T tmp = items[i] + activeRow[j - items[i]];
                if (tmp > activeRow[j])
                    activeRow[j] = tmp;
            }

            if (j == items[i]) {
                const T tmp = items[i] + activeRow[0];
                if (tmp > activeRow[items[i]])
                    activeRow[items[i]] = tmp;
            }
        }

        // Суммарная стоимость предметов
        return activeRow[bagSize];
    }
};

int main()
{
    int N;
    std::cin >> N;
    std::vector<size_t> items(N);

    size_t bagSize = 0;
    for (int i = N-1; i >= 0; i--) {
        std::cin >> items[i];
        bagSize += items[i];
    }

    BackpackSolver<size_t> solver(bagSize>>1,items);
    // Решаем частный случай задачи о рюкзаке
    std::cout << bagSize-2*solver.solve();
}