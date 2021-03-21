#include <iostream>
#include <string>
#include <stack>

/*
Польский калькулятор
Для вычисления арифметических выражений на практике удобно использовать польскую запись. В ней операции записывают перед операндами, а не между как мы привыкли. Таким образом

-  2 1 = (2 - 1)
и
 -   *   /  15  -  7  +  1 1 3  +  2  +  1 1  =  15  /  (7  -  (1  +  1))  *  3  -  (2  +  (1  +  1))

Вам необходимо написать калькулятор, который вычисляет значение арифметического выражения в префиксной записи. Размеры операндов и результаты операций не превосходят 1000.

Формат входных данных
Формат результата

Примеры
Входные данные
+ 1 2
Результат работы
3

Входные данные
- * / 15 - 7 + 1 1 3 + 2 + 1 1
Результат работы
5
*/


struct item{
    bool is_op;
    int value;
    item(bool is_op, int value) :is_op(is_op), value(value) {}
};

int main() {
	std::string input;
    std::getline(std::cin, input);

    std::stack<item> stack;

    size_t i = 0;
    for (size_t j = 1, n = input.size(); j < n; j++) {
        if (input[j] == ' ') {
            if (input[i] == '/' || input[i] == '*' || input[i] == '+' || input[i] == '-')
                stack.push(item(true, input[i]));
            else if (input[i] != ' ') {
                int x = std::stoi(input.substr(i, j - i));

                while (!(stack.empty() || stack.top().is_op)) {
                    int num = stack.top().value; // число
                    stack.pop();

                    switch (stack.top().value) {// операция
                    case '-':
                        x = num-x;
                        break;
                    case '+':
                        x += num;
                        break;
                    case '*':
                        x *= num;
                        break;
                    case '/':
                        x = num/x;
                        break;
                    }
                    stack.pop();
                }

                stack.push(item(false, x));
            }
            i = j++ + 1;
        }
    }

    int result = 0;
    if (i < input.size()) {
        if (input[i] != ' ') {
            result = std::stoi(input.substr(i, input.size() - i));

            while (!stack.empty()) {
                int num = stack.top().value; // число
                stack.pop();

                switch (stack.top().value) {// операция
                case '-':
                    result = num - result;
                    break;
                case '+':
                    result += num;
                    break;
                case '*':
                    result *= num;
                    break;
                case '/':
                    result = num / result;
                    break;
                }
                stack.pop();
            }
        }
    }
    std::cout << result;
	return 0;
}