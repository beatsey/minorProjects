#include <iostream>

/*
Разрезание блинов

На очень большом столе разложено много абсолютно круглых блинов, некоторые из которых могут частично или полностью налегать друг на друга.
Абсолютно прямым ножом проводится луч из первой точки по направлению ко второй.
Требуется определить, какие из блинов будут задеты разрезом. Касания НЕ учитываются.
Формат входных данных
В первой строке — координаты двух точек на плоскости, которые определяют луч разреза.
Во второй строке — количество блинов 1<=N<=100000.
В следующих N строках по три числа — координаты центра блина и его радиус.
Все координаты — целые числа от -10000 до 10000.

Радиус — строго положительное целое число.
Формат результата
Номера разрезанных блинов в порядке возрастания. Нумерация блинов начинается с 1.

Примеры
Входные данные
0 0 0 1
5
-1 -1 1
-2 -2 1
-3 -3 4
1 2 4
3 1 1

Результат работы
4


Входные данные
0 0 0 1
2
3 0 3
3 0 1

Результат работы
(пусто)

*/

int readInt() {
	char ch;
	while (((ch = getchar()) < '0' || ch > '9') && ch!='-');

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

	return minus?-result:result;
}

constexpr void strCpyFast(char*&dest, const char* source) {
	while ((*dest = *source++))dest++;
}
constexpr char* uintToString(unsigned int x, char* bufferEnd) {
	while (x) {
		*--bufferEnd = '0' + x % 10;
		x /= 10;
	}
	return bufferEnd;
}

int main()
{
	const int	x0 = readInt(),
				y0 = readInt(),
				dx = readInt() - x0,
				dy = readInt() - y0,
				len2 = dx * dx + dy * dy; // <= 8e8

	char * const buffer_out = new char[588896], // максимальный размер вывода в случае, если у нас все номера от 1 до 100000 будут выведены через пробел и в конце \0
	     *buffer_end = buffer_out;
	buffer_out[1] = buffer_out[588895] = 0;

	for (unsigned int i=1,N=readInt(); i<=N;i++) {
		int	gx = readInt() - x0,
			gy = readInt() - y0,
			r = readInt(),
			inside = gx * gx + gy * gy - r * r, // если inside<0, то (x0,y0) лежит внутри круга радиуса r с центром в прочитанной точке
			b;
		// если же inside > 0, то проверяем, чтобы точка была в положительной полуплоскости (условие b>=0)
		// и при этом расстояние до прямой было меньше радиуса r (условие b*b > inside*len2)
		if (inside < 0 || ((b = gx * dx + gy * dy) >= 0 && static_cast<long long>(b) * b > static_cast<long long>(inside) * len2)) {
			*buffer_end++ = ' ';
			strCpyFast(buffer_end, uintToString(i, buffer_out + 588895));
		}
	}

	std::cout << (buffer_out + 1) << std::endl; // вывод всего буфера на печать за один вызов
	delete[] buffer_out;
	return 0;
}