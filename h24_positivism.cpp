#include <iostream>

/*
Позитивизм

У Иеремии родители — философы. Он часто слышит их разговоры, но мало что в них понимает. Сам Иеремия учится в информатическом классе физматшколы, и философия его пока не интересует.
Недавно он услышал новое для себя слово: позитивизм. Он постеснялся спросить своих родителей, что это слово обозначает, и узнал в Википедии, что-то про эмпирические и философские исследования.
Так как слово ему понравилось, он загорелся идеей провести какие-то исследования, а так, как недавно в школе они проходили матрицы, вопрос, что же будет объектом исследования, оказался для него очевидным.
Он называет позитивной матрицей такую двумерную матрицу, у которой сумма элементов каждой из строк неотрицательна и сумма элементов каждого из столбцов тоже неотрицательна.

Он поставил перед собой задачу установить, каждую ли из матриц можно сделать позитивной, имея ровно две операции: смену всех знаков на противоположные либо для всех элементов строки, либо для всех элементов столбца.
Операции первого вида он записывал, как l y, где y — номер инвертируемой строки, а второго — как c x, где x — номер инвертируемого столбца. И столбцы и строки нумеруются с нуля.
Он проделал серию экспериментов и убедился, что если решение существует, то оно может быть не единственным.

Ваша задача состоит в том, чтобы помочь Иеремии, написав программу, которая либо сообщит, что не существует такой последовательности операций, чтобы матрица стала позитивной, либо выдаст любую последовательность операций, приводящую в конечном итоге к позитивной матрице.

Формат входных данных
В первой строке — числа N и M — количество строк и столбцов соответственно. Эти числа не превосходят 100.
В каждой из следующих N строк содержатся значения элементов каждой строки. Ни одно из этих чисел по абсолютной величине не превосходит 10e6.

Формат результата
Если матрицу можно сделать позитивной, то решение должно состоять из произвольного числа строк указанного выше вида. Если матрица позитивна с самого начала, программа ничего не должна выводить.
Если её позитивной сделать нельзя, нужно вывести одно слово: Impossible.

Примеры
Входные данные
3 3
1 -10 8
2 1   3
1 7   4

Результат работы
l 0
c 2


Входные данные
2 2
1 2
3 4

Результат работы

*/

int readInt() {
	char ch;
	while (((ch = getchar()) < '0' || ch > '9') && ch != '-');

	bool minus = false;
	int result;

	if (ch == '-') {
		minus = true;
		result = getchar() - '0';
	}
	else {
		result = ch - '0';
	}

	while ((ch = getchar()) >= '0' && ch <= '9')
		result = result * 10 + ch - '0';

	return minus ? -result : result;
}

constexpr void strCpyFast(char*& dest, const char* source) {
	while ((*dest = *source++))dest++;
}
constexpr char* uintToString(unsigned int x, char* bufferEnd) {
	if (x == 0)
		*--bufferEnd = '0';
	else
		while (x) {
			*--bufferEnd = '0' + x % 10;
			x /= 10;
		}
	return bufferEnd;
}

int main()
{
	int N = readInt(), M = readInt();

	bool * inverseRows = new bool[N],
		 * inverseCols = new bool[M];

	int * sumRows = new int[N],
		* sumCols = new int[M];

	for (int i = N - 1; i >= 0; i--) {
		sumRows[i] = 0;
		inverseRows[i] = false;
	}

	for (int j = M - 1; j >= 0; j--) {
		sumCols[j] = 0;
		inverseCols[j] = false;
	}

	// allocate matrix
	int** matrix = new int* [N];
	for (int i = N - 1; i >= 0; i--)
		matrix[i] = new int[M];

	// read matrix
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			int input = readInt();
			matrix[i][j] = input;
			sumRows[i] += input;
			sumCols[j] += input;
		}
	}

	// make cycle k times before declaring it is impossible
	bool stuffHappening = true;
	for (int k = 10; stuffHappening && k > 0;k--) {
		stuffHappening = false;

		// make matrix row-positive
		for (int i = 0; i < N; i++) {
			if (sumRows[i] >= 0) continue;

			for (int j = M - 1; j >= 0; j--) {
				sumCols[j] -= 2 * matrix[i][j];
				matrix[i][j] = -matrix[i][j];
			}

			sumRows[i] = -sumRows[i];
			inverseRows[i] ^= true;
			stuffHappening = true;
		}

		// make matrix col-positive
		for (int j = M - 1; j >= 0; j--) {
			if (sumCols[j] >= 0) continue;

			for (int i = N - 1; i >= 0; i--) {
				sumRows[i] -= 2 * matrix[i][j];
				matrix[i][j] = -matrix[i][j];
			}

			sumCols[j] = -sumCols[j];
			inverseCols[j] ^= true;
			stuffHappening = true;
		}
	}

	// output
	{
		bool impossible = false;
		// matrix now is col-positive
		// check is it is still row-positive
		if (stuffHappening) {
			for (int i = N - 1; i >= 0; i--) {
				if (sumRows[i] >= 0) continue;

				impossible = true;
				break;
			}
		}

		if (impossible) {
			std::cout << "Impossible" << std::endl;
		}
		else {
			char* const buffer = new char[5 * 100 * 100 + 1],
				* buffer_end = buffer;
			buffer[1] = buffer[5 * 100 * 100] = 0;

			for (int i = N - 1; i >= 0; i--) {
				if (inverseRows[i]) {
					strCpyFast(buffer_end, "\nl ");
					strCpyFast(buffer_end, uintToString(i, buffer + 5 * 100 * 100));
				}
			}

			for (int j = M - 1; j >= 0; j--) {
				if (inverseCols[j]) {
					strCpyFast(buffer_end, "\nc ");
					strCpyFast(buffer_end, uintToString(j, buffer + 5 * 100 * 100));
				}
			}
			std::cout << (buffer + 1) << std::endl;
			delete[] buffer;
		}
	}

	// free memory
	for (int i = N - 1; i >= 0; i--)
		delete[] matrix[i];

	delete[] matrix;
	delete[] sumRows;
	delete[] sumCols;
	delete[] inverseRows;
	delete[] inverseCols;

	return 0;
}