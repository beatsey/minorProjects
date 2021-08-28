/*
Задача 5: 5
Дано натуральное число N. Рассмотрим его разбиение на различные натуральные слагаемые. Два разбиения, отличающихся только порядком слагаемых, будем считать за одно, поэтому можно считать, что слагаемые в разбиении упорядочены по невозрастанию.

Формат входных данных
Задано единственное число N. (N <= 40)

Формат результата
Необходимо вывести все разбиения числа N на различные натуральные слагаемые в обратном лексикографическом порядке.

Примеры
Входные данные
5
Результат работы
5
4 1
3 2
3 1 1
2 2 1
2 1 1 1
1 1 1 1 1

*/

#include <iostream> 
#include <vector>

class Decompose {
	Decompose() {}

static void decompose_recursively(int curNumber, std::vector<int>& array) {
	if (curNumber == 0) {
		for (const int el : array)
			printf("%d ", el);

		printf("\n");
		return;
	}

	int x = (!array.empty() && curNumber > array.back()) ? array.back() : curNumber;
	for (; x >= 1; --x) {
		array.push_back(x);
		decompose_recursively(curNumber - x, array);
		array.pop_back();
	}
}

public:
	static void decompose(int curNumber) {
		std::vector<int> array;
		decompose_recursively(curNumber, array);
	}
};

int main()
{
	int n;
	std::cin >> n;
	Decompose::decompose(n);
}