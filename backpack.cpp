#include <iostream>
#include <vector>
#include <string>
#include <sstream>

/*
ЗАДАЧА О РЮКЗАКЕ

Решить задачу о рюкзаке методом динамического программирования. Алгоритм должен быть инкапсулирован.

Формат входных данных
Данные подаются на стандартный поток ввода. Пустые строки игнорируются.
Первая строка содержит натуральное число - максимальную массу предметов, которую выдержит рюкзак.
Каждая последующая содержит два неотрицательных числа: массу предмета и его стоимость.

Формат результата
Первая строка содержит два числа: суммарную массу предметов и их суммарную стоимость.
В последующих строках записаны номера предметов, которые были помещены в рюкзак, в порядке возрастания номера.
Результат работы программы выводится в стандартный поток вывода.
В любой непонятной ситуации результатом работы любой команды будет "error".

Пример
Входные данные	
165
23 92
31 57
29 49
44 68
53 60
38 43
63 67
85 84
89 87
82 72

Результат работы
165 309
1
2
3
4
6
*/
template <class T>
struct Item {
    T mass;
    T value;
    Item(T mass, T value):mass(mass), value(value) {}
};

template <class T>
struct Result {
    T spaceTaken;
    T value;
    std::vector<size_t> indices;
    Result(T spaceTaken, T value):spaceTaken(spaceTaken), value(value) {}
};

template <class T>
class BackpackSolver;

template <class T>
std::istream& operator>>(std::istream& istr, BackpackSolver<T>& solver) {

    std::string input;
    // Считываем размер рюкзака
    while (std::getline(istr, input)) {
        if (input.length() == 0)
            continue;

        char c;
        long num;
        std::istringstream stream(input);
        if ((stream >> num) && (num >= 0) && !stream.get(c)) {
            solver.bagSize = static_cast<T>(num);
            break;
        }

        std::cout << "error" << std::endl;
    }

    // Считываем предметы
    while (std::getline(istr, input)) {
        if (input.length() == 0)
            continue;

        char c;
        long num1, num2;
        std::istringstream stream(input);

        if ((stream >> num1) && (stream >> num2) && (num1 >= 0) && (num2 >= 0) && !stream.get(c)) {
            solver.items.push_back({ static_cast<T>(num1), static_cast<T>(num2) });
            continue;
        }

        std::cout << "error" << std::endl;
    }

    return istr;
}

template <class T>
class BackpackSolver {

    // Размер рюкзака
    T bagSize;

    // Массив предметов
    std::vector<Item<T>> items;

    std::vector<std::vector<T>> matrix;

    size_t getMaxCommonFactor(size_t x, size_t y) {
        size_t tmp;

        while (tmp = x % y) {
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
            MCF = getMaxCommonFactor(items[i].mass, MCF);
            if (MCF <= 1) return 1;
        }

        bagSize /= MCF;
        for (size_t i = 0, n = items.size(); i < n; i++) {
            items[i].mass /= MCF;
        }

        return MCF;
    }

    void buildMemoizeTable() {
        // Все N предметов находятся в items
        std::vector<T> activeRow(bagSize + 1, 0);

        matrix.resize(items.size() + 1);
        matrix[0] = activeRow;

        for (size_t i = 0, N = items.size(); i < N; i++) {
            T j;
            for (j = bagSize; j > items[i].mass; --j) {
                const T tmp = items[i].value + activeRow[j - items[i].mass];
                if (tmp > activeRow[j])
                    activeRow[j] = tmp;
            }

            if (j == items[i].mass) {
                const T tmp = items[i].value + activeRow[0];
                if (tmp > activeRow[items[i].mass])
                    activeRow[items[i].mass] = tmp;
            }
            // Запомнили копию активной строки
            matrix[i + 1] = activeRow;
        }
    }

public:
    BackpackSolver():bagSize(0){}
    Result<T> solve() {

        // Множитель для сокращения масс предметов и рюкзака
        T multiplier = reduceMasses();

        buildMemoizeTable();

        const size_t N = matrix.size() - 1;
        T bagSizeTmp = bagSize;

        // Суммарная стоимость предметов
        T maxSumValue = matrix[N][bagSize];

        // Идём искать влево по матрице реальную заполненность рюкзака
        while ((bagSizeTmp > 0) && (matrix[N][bagSizeTmp - 1] == maxSumValue))
            bagSizeTmp--;


        // Занимаемое место, стоимость
        Result<T> res(bagSizeTmp * multiplier, maxSumValue);
        

        for (size_t i = N; i > 0; i--) {
            // Неравенство говорит о том, что предмет был положен в рюкзак
            if (matrix[i][bagSizeTmp] == matrix[i - 1][bagSizeTmp])
                continue;
            res.indices.push_back(i);
            bagSizeTmp -= items[i - 1].mass;
        }

        matrix.clear();

        return res;
    }

    friend std::istream& operator>> <T>(std::istream&, BackpackSolver<T>&);
};

template <class T>
std::ostream& operator<<(std::ostream& stream, const Result<T>& res) {
    stream << res.spaceTaken << ' ' << res.value << std::endl;
    for (size_t i = res.indices.size(); i > 0; i--) {
        std::cout << res.indices[i - 1] << std::endl;
    }
    return stream;
}
int main()
{
    BackpackSolver<size_t> solver;

    std::cin >> solver;
    std::cout << solver.solve();
}
