/*
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
#include <list> 

using namespace std;

int n;
list<int> a;

void rec(int curNumber) {
	if (curNumber == 0) {
		for (const auto& el : a) {
			cout << el << ' ';
		}
		cout << endl;
		return;
	}

	int fir = 1;
	
	if (!a.empty() && curNumber > a.back()) {
		for (int x = a.back(); x >= 1; --x) {
			a.push_back(x);
			rec(curNumber - x);
			a.pop_back();
		}
		return;
	}

	for (int x = curNumber; x >= fir; --x) {
		a.push_back(x);
		rec(curNumber - x);
		a.pop_back();
	}
}

int main()
{
	cin >> n;
	rec(n);
}