"""
Быстрая сортировка
Реализуйте эффективный алгоритм быстрой сортировки, который обсуждался на семинаре.

Формат входных данных
Ввод осуществляется со стандартного потока ввода.
Первая и единственная строка всегда содержит входной массив.
Все данные гарантированно валидны, проверять данные на корректность не нужно.

Формат результата
Результат работы - отсортированный массив.
Результат работы программы выводится в стандартный поток вывода.

Пример
Входные данные
4 3 5 1 2

Результат работы
1 2 3 4 5

"""
import random

def quicksort(array):
    def qsort(left,right):
        if right<=left:
            return

        num = random.randint(left, right)
        pivot = array[num]
        array[num],array[right]=array[right],pivot

        r = right-1
        l = left

        while True:
            for l in range(l,right+1):
                if array[l]>=pivot:
                    break

            for r in range(r,l-1,-1):
                if array[r]<pivot:
                    break

            if l<r:
                array[l],array[r]=array[r],array[l]
                l+=1
                r-=1
            else:
                array[l],array[right]=pivot,array[l]
                qsort(left,l-1)
                qsort(l+1,right)
                return

    qsort(0,len(array)-1)

array = [int(X) for X in input().split(' ')]
quicksort(array)
print(' '.join([str(x) for x in array]))