#include <iostream>
#include <vector>
#include <array>
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

class BackpackSolver {
    // Размер рюкзака
    size_t bagSize;
    // Занятое место предметами после решения задачи
    size_t realSpaceTaken;
    // Суммарная ценность предметов после решения задачи
    size_t maxSumValue;
    // Множитель для сокращения масс предметов и рюкзака
    size_t multiplier;

    // Исходные предметы
    std::vector<std::array<int, 2>> items;
    // Матрица для решения задачи
    std::vector<std::vector<int>> matrix;
    // Результирующий массив индексов предметов
    std::vector<size_t> result;

    // Функция читает поток ввода, добавляет предметы в items и возвращает размер рюкзака
    void parseInput() {
        items.clear();

        std::string input;
        // Считываем размер рюкзака
        while (std::getline(std::cin, input)) {
            if (input.length() == 0)
                continue;

            char c;
            std::istringstream stream(input);
            if ((stream >> bagSize) && !stream.get(c)) {
                break;
            }
            else {
                std::cout << "error" << std::endl;
            }
        }

        // Считываем предметы
        while (std::getline(std::cin, input)) {
            if (input.length() == 0)
                continue;

            char c;
            int num1, num2;
            std::istringstream stream(input);

            if ((stream >> num1) && (stream >> num2) && !stream.get(c)) {
                items.push_back({ num1, num2 });
                continue;
            }

            std::cout << "error" << std::endl;
        }
    }

    // Возвращает true, если factor является общим множителем всех масс и массы рюкзака
    bool isCommonFactor(size_t factor) {
        if (bagSize % factor != 0)
            return false;

        for (size_t j = 0; j < items.size(); j++) {
            if (items[j][0] % factor != 0)
                return false;
        }

        return true;
    }

    // Для больших масс получается слишком много столбцов в матрице
    // Можно найти общий множитель у всех масс и размером рюкзака и кратно уменьшить сложность задачи
    // Функция возвращает множитель
    size_t reduceMasses() {
        size_t factors[] = { 1000, 100, 10, 2, 3, 5, 7 };

        multiplier = 1;

        if (bagSize == 0) return 1;

        for (size_t i = 0, n = sizeof(factors) / sizeof(size_t); i < n; i++) {

            // Сокращаем на factors[i], пока делится
            while (isCommonFactor(factors[i])) {
                multiplier *= factors[i];
                bagSize /= factors[i];
                for(size_t k = 0; k<items.size();k++)
                    items[k][0] /= factors[i];
            }
        }
        
    }

    void getMemoizeTableFromInput() {
        // Все N предметов находятся в items
        const size_t N = items.size();

        std::vector<int> activeRow(bagSize + 1, 0);

        matrix.resize(N + 1);
        matrix[0] = activeRow;

        for (size_t i = 0; i < N; i++) {
            // items[i][0] - масса; items[i][1] - стоимость
            const int mass = items[i][0];
            const int value = items[i][1];
            
            for (int j = bagSize; j >= mass; --j) {
                const int tmp = value + activeRow[j - mass];
                if (tmp > activeRow[j])
                    activeRow[j] = tmp;
            }

            // Запомнили (копию) активной строки
            matrix[i + 1] = activeRow;
        }
    }

public:
    void solveBackPackTask() {
        parseInput();
        reduceMasses();
        getMemoizeTableFromInput();

        const size_t N = matrix.size() - 1;
        int bagSizeTmp = bagSize;

        // Фиксируем максимальную стоимость предметов
        maxSumValue = matrix[N][bagSizeTmp];

        // Идём искать влево по матрице реальную заполненность рюкзака
        while ((bagSizeTmp > 0) && (matrix[N][bagSizeTmp - 1] == maxSumValue))
            bagSizeTmp--;

        // Фиксируем сколько место реально занято в рюкзаке
        realSpaceTaken = bagSizeTmp;

        // Собираем индексы добавленных предметов
        result.clear();
        for (size_t i = N; i > 0; i--) {
            // Неравенство говорит о том, что предмет был положен в рюкзак
            if (matrix[i][bagSizeTmp] == matrix[i - 1][bagSizeTmp])
                continue;
            result.push_back(i);
            bagSizeTmp -= items[i - 1][0];
        }

        // Очищаем место
        items.clear();
        matrix.clear();
    }

    void printResult() {
        // realSpaceTaken, maxSumValue - место и стоимость предметов
        // result - массив индексов предметов
        std::cout << (realSpaceTaken*multiplier) << ' ' << maxSumValue << std::endl;
        for (size_t i = result.size(); i > 0; i--) {
            std::cout << result[i - 1] << std::endl;
        }
    }

};

int main()
{
    BackpackSolver solver;
    solver.solveBackPackTask();
    solver.printResult();
}