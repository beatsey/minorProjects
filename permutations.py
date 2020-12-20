"""
Перестановки
Реализуйте алгоритм генерации перестановок с началом в произвольной перестановке.
Реализация алгоритма должна быть инкапсулирована и не зависеть от ввода/вывода.

Формат входных данных
На стандартном потоке ввода в первой и единственной строке задаётся перестановка — несколько чисел, разделенных пробелами.

Формат результата
На стандартный поток вывода выводятся построчно все последующие перестановки, включая входную, в лексикографическом порядке.

Пример
Входные данные
3 2 1 4

Результат работы
3 2 1 4
3 2 4 1
3 4 1 2
3 4 2 1
4 1 2 3
4 1 3 2
4 2 1 3
4 2 3 1
4 3 1 2
4 3 2 1
1 2 3 4
1 2 4 3
1 3 2 4
1 3 4 2
1 4 2 3
1 4 3 2
2 1 3 4
2 1 4 3
2 3 1 4
2 3 4 1
2 4 1 3
2 4 3 1
3 1 2 4
3 1 4 2

"""


def getNextPermutation(perm):
    def getFirstGreaterIndex(array,x):
        for i in range(len(array)):
            if x<array[i]:
                return i
        return -1

    if len(perm)==1:
        return perm

    for i in range(len(perm)-2,-1,-1):
        if perm[i]<perm[i+1]:
            perm[i+1::]=sorted(perm[i+1::])
            firstGreater = getFirstGreaterIndex(perm[i+1::],perm[i]) + (i+1)
            perm[i],perm[firstGreater]=perm[firstGreater],perm[i]
            return perm
    return perm[::-1]

try:
    P = [int(X) for X in input().split(' ')]
    initial = list(P)

    out=''
    while True:
        out+=' '.join([str(x) for x in P])+'\n'
        P = getNextPermutation(P)
        if P==initial:
            break
    print(out,end='')
except ValueError:
    pass