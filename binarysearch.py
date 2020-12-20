"""
Бинарный поиск
Реализуйте рекурсивно алгоритм бинарного поиска.
Реализация алгоритма должна быть инкапуслирована, т.е. не зависеть от форматов входных/выходных данных и непосредственно ввода/вывода.

Формат входных данных
Ввод осуществляется со стандартного потока ввода.
Первая строка всегда содержит отсортированный массив, в котором должен производится поиск.
Остальные строки имеют формат search K, где K - некоторое число.
Все данные гарантированно валидны, проверять данные на корректность не нужно.

Формат результата
Результат поиска - индекс числа в массиве. Если число в массиве отсутствует, то результатом будет -1.
Результат работы программы выводится в стандартный поток вывода.

Пример
Входные данные	
10 20 30 40 50 60 70 80
search 30
search 5

Результат работы
2
-1

"""

def binarySearch2(array, x):
    def binsearch2(low, high):
        if high < low:
            return -1
        middle = (high + low) >> 1
        if x==array[middle]:
            return middle
        elif x>array[middle]:
            return binsearch2(middle + 1, high)
        else:
            return binsearch2(low, middle - 1)

    return binsearch2(0,len(array)-1)

def binarySearch(array,x):
    def binsearch(array):
        if len(array)==1:
            return 0 if array[0]==x else -1

        middle = len(array)>>1
        if x>=array[middle]:
            search = binsearch(array[middle::])
            return -1 if search==-1 else search+middle
        else:
            return binsearch(array[:middle:])
        
    return -1 if len(array)==0 else binsearch(array)

array = [int(X) for X in input().split(' ')]

while True:
    try:
        K = int(input().split(' ')[1])
    except EOFError:
        break
    except KeyboardInterrupt:
        break
       
    print(binarySearch(array,K))