'''
Калькулятор

Имеется калькулятор, который выполняет следующие операции:
* умножить число X на 2
* умножить число X на 3
* прибавить к числу X единицу

Определите, какое наименьшее количество операций требуется, чтобы получить из числа 1 число N.

Формат ввода
Во входном файле написано натуральное число N, не превосходящее 10^6.

Формат вывода
В первой строке выходного файла выведите минимальное количество операций. Во второй строке выведите числа, последовательно получающиеся при выполнении операций. Первое из них должно быть равно 1, а последнее N. Если решений несколько, выведите любое.

1

0
1



5

3
1 3 4 5

'''

def shortestpath(x, current_path):
    if array[x] != -1:
        return array[x]

    if current_path >= shortest:
        return n

    array[x] = x - 1
    if x % 3 == 0:
        array[x] = min(array[x], shortestpath(x // 3, current_path + 1))
    if x % 2 == 0:
        array[x] = min(array[x], shortestpath(x // 2, current_path + 1))

    array[x] = min(array[x], shortestpath(x - 1, current_path + 1)) + 1
    return array[x]


n = int(input())
array = [-1] * (n + 1)
array[1] = 0
shortest = 36
shortestpath(n, 0)

result = [n]

while n != 1:
    k = n

    if n % 3 == 0:
        k = n // 3
    if n % 2 == 0 and array[n // 2] < array[k]:
        k = n // 2
    if array[n - 1] < array[k]:
        k = n - 1

    result.append(k)
    n = k

print(len(result) - 1)
print(*result[::-1])
