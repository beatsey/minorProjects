"""
E. Кубики
Ограничение времени  1 секунда
Ограничение памяти  64Mb
Ввод  стандартный ввод или input.txt
Вывод  стандартный вывод или output.txt

Аня и Боря любят играть в разноцветные кубики, причем у каждого из них свой набор и в каждом наборе все кубики различны по цвету. Однажды дети заинтересовались, сколько существуют цветов таких, что кубики каждого цвета присутствуют в обоих наборах. Для этого они занумеровали все цвета случайными числами. На этом их энтузиазм иссяк, поэтому вам предлагается помочь им в оставшейся части. Номер любого цвета — это целое число в пределах от 0 до 109.

Формат ввода
В первой строке входного файла записаны числа N и M — количество кубиков у Ани и Бори соответственно. В следующих N строках заданы номера цветов кубиков Ани. В последних M строках номера цветов кубиков Бори.

Формат вывода
Выведите сначала количество, а затем отсортированные по возрастанию номера цветов таких, что кубики каждого цвета есть в обоих наборах, затем количество и отсортированные по возрастанию номера остальных цветов у Ани, потом количество и отсортированные по возрастанию номера остальных цветов у Бори.

Пример 1
Ввод
4 3
0
1
10
9
1
3
0
Вывод
2
0 1
2
9 10
1
3

Пример 2
Ввод
2 2
1
2
2
3
Вывод
1
2
1
1
1
3

Пример 3
Ввод
0 0
Вывод
0
0
0
"""
import numpy as np
array=input().split(' ')
N=int(array[0])
M=int(array[1])
stonesAnn=np.asarray([int(input()) for i in range(N)])
stonesBoris=np.asarray([int(input()) for i in range(M)])

stonesALL=np.concatenate((stonesAnn,stonesBoris))
unique, counts=np.unique(stonesALL, return_counts=True)

arrDuplicates=unique[counts>1]
np.sort(arrDuplicates)

print(len(arrDuplicates))
print(" ".join(arrDuplicates.astype(str)))

arrUnique=unique[counts==1]
annUnique=np.intersect1d(arrUnique,stonesAnn)
np.sort(annUnique)

print(len(annUnique))
print(" ".join(annUnique.astype(str)))

borisUnique=np.intersect1d(arrUnique,stonesBoris)
np.sort(borisUnique)

print(len(borisUnique))
print(" ".join(borisUnique.astype(str)))

