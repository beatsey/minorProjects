"""
Транспонирование матрицы

Есть матрица размера m x n. Нужно написать функцию, которая её транспонирует. Транспонированная матрица получается из исходной заменой строк на столбцы.

Формат ввода
В первой строке задано число m - количество строк матрицы.
Во второй строке задано n - число столбцов.
m,n<=1000

В следующих n строках задана матрица. Числа в ней не превосходят по модулю 1000.

Формат вывода
Напечатайте транспонированную матрицу в том же формате, который задан во входных данных. Каждая строка матрицы выводится на отдельной строке, элементы разделяются пробелами.

Пример
4
3
1 2 3
0 2 6
7 4 1
2 7 0

1 0 7 2
2 2 4 7
3 6 1 0


9
5
-7 -1 0 -4 -9
5 -1 2 2 9
3 1 -8 -1 -7
9 0 8 -8 -1
2 4 5 2 8
-7 10 0 -4 -8
-3 10 -7 10 3
1 6 -7 -5 9
-1 9 9 1 9

-7 5 3 9 2 -7 -3 1 -1
-1 -1 1 0 4 10 10 6 9
0 2 -8 8 5 0 -7 -7 9
-4 2 -1 -8 2 -4 10 -5 1
-9 9 -7 -1 8 -8 3 9 9
"""

class WrongInputException(Exception):
    def __init__(self):
        pass


def transpose(mat,rows,cols):
    matTranspose=[]
    for c in range(cols):
        matTranspose.append([])
        for r in range(rows):
            matTranspose[-1].append(mat[r][c])
    return matTranspose

def printMatrix(mat):
    for row in mat:
        for value in row:
            print(value,end=' ')
        print()

n=int(input())
m=int(input())
matrix=[]
for i in range(n):
    row=[int(x) for x in input().split(' ')]
    if len(row)!=m:
        raise WrongInputException
    else:
        matrix.append(row)

printMatrix(transpose(matrix,n,m))