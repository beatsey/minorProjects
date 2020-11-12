#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <sstream>

/*
������ � �������

������ ������ � ������� ������� ������������� ����������������. �������� ������ ���� ��������������.

������ ������� ������
������ �������� �� ����������� ����� �����. ������ ������ ������������.
������ ������ �������� ����������� ����� - ������������ ����� ���������, ������� �������� ������.
������ ����������� �������� ��� ��������������� �����: ����� �������� � ��� ���������.

������ ����������
������ ������ �������� ��� �����: ��������� ����� ��������� � �� ��������� ���������.
� ����������� ������� �������� ������ ���������, ������� ���� �������� � ������, � ������� ����������� ������.
��������� ������ ��������� ��������� � ����������� ����� ������.
� ����� ���������� �������� ����������� ������ ����� ������� ����� "error".

������
������� ������	
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

��������� ������
165 309
1
2
3
4
6
*/

class BackpackSolver {
    // ������ �������
    size_t bagSize;
    // ������� ����� ���������� ����� ������� ������
    size_t realSpaceTaken;
    // ��������� �������� ��������� ����� ������� ������
    size_t maxSumValue;
    // ��������� ��� ���������� ���� ��������� � �������
    size_t multiplier;

    // �������� ��������
    std::vector<std::array<int, 2>> items;
    // ������� ��� ������� ������
    std::vector<std::vector<int>> matrix;
    // �������������� ������ �������� ���������
    std::vector<size_t> result;

    // ������� ������ ����� �����, ��������� �������� � items � ���������� ������ �������
    void parseInput() {
        items.clear();

        std::string input;
        // ��������� ������ �������
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

        // ��������� ��������
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

    // ���������� true, ���� factor �������� ����� ���������� ���� ���� � ����� �������
    bool isCommonFactor(size_t factor) {
        if (bagSize % factor != 0)
            return false;

        for (size_t j = 0; j < items.size(); j++) {
            if (items[j][0] % factor != 0)
                return false;
        }

        return true;
    }

    // ��� ������� ���� ���������� ������� ����� �������� � �������
    // ����� ����� ����� ��������� � ���� ���� � �������� ������� � ������ ��������� ��������� ������
    // ������� ���������� ���������
    size_t reduceMasses() {
        size_t factors[] = { 1000, 100, 10, 2, 3, 5, 7 };

        multiplier = 1;

        if (bagSize == 0) return 1;

        for (size_t i = 0, n = sizeof(factors) / sizeof(size_t); i < n; i++) {

            // ��������� �� factors[i], ���� �������
            while (isCommonFactor(factors[i])) {
                multiplier *= factors[i];
                bagSize /= factors[i];
                for(size_t k = 0; k<items.size();k++)
                    items[k][0] /= factors[i];
            }
        }
        
    }

    void getMemoizeTableFromInput() {
        // ��� N ��������� ��������� � items
        const size_t N = items.size();

        std::vector<int> activeRow(bagSize + 1, 0);

        matrix.resize(N + 1);
        matrix[0] = activeRow;

        for (size_t i = 0; i < N; i++) {
            // items[i][0] - �����; items[i][1] - ���������
            const int mass = items[i][0];
            const int value = items[i][1];
            
            for (int j = bagSize; j >= mass; --j) {
                const int tmp = value + activeRow[j - mass];
                if (tmp > activeRow[j])
                    activeRow[j] = tmp;
            }

            // ��������� (�����) �������� ������
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

        // ��������� ������������ ��������� ���������
        maxSumValue = matrix[N][bagSizeTmp];

        // ��� ������ ����� �� ������� �������� ������������� �������
        while ((bagSizeTmp > 0) && (matrix[N][bagSizeTmp - 1] == maxSumValue))
            bagSizeTmp--;

        // ��������� ������� ����� ������� ������ � �������
        realSpaceTaken = bagSizeTmp;

        // �������� ������� ����������� ���������
        result.clear();
        for (size_t i = N; i > 0; i--) {
            // ����������� ������� � ���, ��� ������� ��� ������� � ������
            if (matrix[i][bagSizeTmp] == matrix[i - 1][bagSizeTmp])
                continue;
            result.push_back(i);
            bagSizeTmp -= items[i - 1][0];
        }

        // ������� �����
        items.clear();
        matrix.clear();
    }

    void printResult() {
        // realSpaceTaken, maxSumValue - ����� � ��������� ���������
        // result - ������ �������� ���������
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