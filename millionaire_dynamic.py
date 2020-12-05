"""
Сумасшедший богач
Один сумасшедший богач на старости лет впал в маразм и стал еще более сумасшедшим. Он решил отдать половину своих богатств тому, кто выиграет в математической игре.

Правила игры: изначально каждый игрок начинает с нулевой суммой. Он может либо получить у богача 1 миллион сантиков, либо отдать ему 1 миллион сантиков, либо получить от богача ту же сумму, которая есть у него сейчас.

Выигрывает тот, кто за минимальное количество действий наберет сумму, равную половине состояния богача.

На беду других игроков, нашелся человек, который что-то слышал про жадные алгоритмы и двоичную систему счисления (возможно это вы).

Формат входных данных
В стандартном потоке записано единственное натуральное число - размер половины состояния богача (в миллионах).

Формат результата
Каждая строка выхода содержит ровно одну операцию (inc, dec или dbl) из кратчайшей последовательности действий для победы.

Результат работы программы выводится в стандартный поток вывода.

Примеры
Входные данные
23

Результат работы
inc
dbl
inc
dbl
dbl
dbl
dec
"""

# Словарь троек (число шагов, индекс откуда, индекс операции: 0 - inc, 1 - dec, 2 - dbl, 3 - {dbl+dec}, 4 - {dbl+inc})
# Оптимальные правила: x % 2 == 0 -> делим
# x % 2 == 1 -> min(f(x+1),f(x-1))

# Строим словарик с конца
def getCostDictionary(x):
    def subfunc(x):
        if(x>1):
            currentLength = dict[x][0]
            if x%2==0:
                newX = x//2
                if newX not in dict or dict[newX][0]>currentLength+1:
                    dict[newX]=(currentLength+1,x,2)
                    dictFlags[newX]=True
            else:
                # x нечетный
                x1 = (x+1)//2
                if x1 not in dict or dict[x1][0]>currentLength+1:
                    dict[x1]=(currentLength+2,x,3)
                    if x1>1:
                        dictFlags[x1]=True

                x2 = (x-1)//2
                if x2 not in dict or dict[x2][0]>currentLength+1:
                    dict[x2]=(currentLength+2,x,4)
                    dictFlags[x2]=True
        del dictFlags[x]
    
    # Число шагов = 0 для начального элемента
    dict={x:[0]}
    dictFlags = {x:True}
    
    while(bool(dictFlags)):
        for x in dictFlags.copy():
            subfunc(x)
    if x>0:
        dict[0]=(dict[1][0]+1,1,0)
    
    return dict

def printBestSequence(dict,target):
    elem = dict[0]
    while elem[0]!=0:
        operation = elem[2]
        if operation == 0:
            print('inc')
        else:
            print('dbl')
            if operation == 3:
                print('dec')
            elif operation == 4:
                print('inc')
        elem = dict[elem[1]]

x = int(input())
dict = getCostDictionary(x)
printBestSequence(dict,x)