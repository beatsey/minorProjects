/*
ƒана строка.
“ребуетс€ заменить все целые положительные числа в ней на двоичные аналоги (перевести из дес€тичной в двоичную систему счислени€).

‘ормат ввода
Ќа вход подаетс€ строка из не более 255 символов, среди которых могут быть и пробельные.
√арантируетс€, что числа в строке не начинаютс€ с 0.

ѕримеры
192873a kjhfd129380
101111000101101001a kjhfd11111100101100100

6a8g923mx
110a1000g1110011011mx

*/

#include <iostream>

char divideAndRemainder(char* x) {
	char carry = 0;
	bool flag = false;
	int pos = 0;
	for (int i = 0; x[i] != 0; i++) {
		char c = x[i] - '0';
		x[pos] = (10 * carry + c) / 2 + +'0';

		if (x[pos] != '0')
			flag = true;

		if (flag)
			pos++;

		carry = c % 2;
	}
	x[pos] = 0;

	return carry + '0';
}

char* getBinary(char* x) {
	char* result = new char[849];
	int len = 0;
	while (x[0] != 0) {
		result[len++] = divideAndRemainder(x);
	}

	result[len] = 0;

	for (int i = len / 2 - 1; i >= 0; i--) {
		char c = result[len - i - 1];
		result[len - i - 1] = result[i];
		result[i] = c;
	}

	return result;
}

int main()
{

	char str[256], digit[256], result[849]; // 848 - длина двоичного вида числа 10^256 - 1
	std::cin.getline(str, 256);

	int result_len = 0;
	int digit_len = 0;
	for (int i = 0; str[i] != 0; i++) {
		if (isdigit(str[i])) {
			digit[digit_len++] = str[i];
			digit[digit_len] = 0;
		}
		else {
			if (digit_len > 0) {
				char* binary = getBinary(digit);
				int index = 0;
				while (binary[index]) {
					result[result_len++] = binary[index++];
				}
				delete[] binary;

				digit_len = 0;
			}
			result[result_len++] = str[i];
		}
	}

	if (digit_len > 0) {
		char* binary = getBinary(digit);
		int index = 0;
		while (binary[index]) {
			result[result_len++] = binary[index++];
		}
		delete[] binary;

		digit_len = 0;
	}
	result[result_len] = 0;

	std::cout << result << std::endl;
}