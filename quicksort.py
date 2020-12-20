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

def quicksort(array):
    def qsort(left,right):
        if right<left:
            return

        l = left
        r = right

        pivot = array[r+1]
        while True:
            for l in range(l,right+2):
                if array[l]>=pivot:
                    break

            for r in range(r,l-1,-1):
                if array[r]<pivot:
                    break

            if l<r:
                array[l],array[r]=array[r],array[l]
                l+=1
            else:
                if l==r:
                    array[l],array[right+1]=pivot,array[l]

                    qsort(left,l-2)
                    qsort(l+1,right)
                else:
                    qsort(left,right-1)
                return

    qsort(0,len(array)-2)

array = [int(X) for X in input().split(' ')]
quicksort(array)
print(' '.join([str(x) for x in array]))