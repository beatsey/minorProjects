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


Суть алгоритма заключается в том, что мы рассматриваем задачу с точки зрения построения заданного двоичного числа из 0 с помощью операций сдвига влево (dbl), +1 (inc) и -1 (dec).
Для N подряд идущих единиц оптимальной стратегией будет inc dbl (N раз) dec, когда N>=3. Или (inc dbl) (N раз) для 0<N<3.
Но есть исключения. Например для последовательности 111011 оптимальной стратегией будет inc dbl dbl dbl dbl dec dbl dbl dec.
То есть на оптимальную стратегию получения последовательности единиц влияет предшествующие биты. Поэтому и возникает столько много ситуаций.

Вычислительная сложность O(N), где N - длина двоичной записи исходного числа.
Сложность по памяти O(N). Т.к. требуется выделить для каждого бита числа как минимум один байт, соответствующий команде. 
Можно реализовать за O(1) от памяти, но тогда прийдётся очень часто вызывать функцию print, что приведёт к сильным задержкам по сравнению с реализацией через запоминание результата работы программы и вызова только один раз печати.

Вычислительная сложность эффективнее, чем O(N) не может быть, т.к. для точного решения требуется пройти каждый бит числа хотя бы раз.
"""

def getBestSequenceFastest(target):
    if target <=0:
        return ''
        
    result = ''

    consequentOnes = 0
    consequentZeros = 0
    flagLeadOne = True
    flagDecDblSequence = False

    for length in range(target.bit_length() - 1,-1,-1):
        if (target >> length & 1) == 0:
            consequentZeros += 1
            continue

        if consequentZeros == 0:
            consequentOnes += 1
            continue

        if flagDecDblSequence:
            result+='dbl\n'* consequentOnes
            if consequentZeros == 1:
                result+='dbl\ndec\n'
            else:
                flagDecDblSequence = False
                result+='dec\n'+'dbl\n'*consequentZeros

        elif consequentOnes >= 3:
            result+='inc\n'+'dbl\n'*consequentOnes
            flagLeadOne = False

            if consequentZeros == 1:
                flagDecDblSequence = True
                result+='dbl\ndec\n'
            else:
                result+='dec\n'+'dbl\n'*consequentZeros

        elif flagLeadOne:
            result+='inc\ndbl\n'*consequentOnes+'dbl\n'*(consequentZeros-1)
            flagLeadOne = False
        elif consequentOnes == 2 and consequentZeros == 1:
            flagDecDblSequence = True
            result+='inc\ndbl\ndbl\ndbl\ndec\n'
        else:
            result+='dbl\ninc\n'*consequentOnes+'dbl\n'*consequentZeros

        consequentZeros = 0
        consequentOnes = 1
    #end for

    # Обрабатываем последние 1..10..0
    if flagDecDblSequence:
        result+='dbl\n'*consequentOnes+'dec\n'
    elif consequentOnes >= 3:
        result+='inc\n'+'dbl\n'*consequentOnes+'dec\n'
    elif flagLeadOne:
        result+='inc\n'+'dbl\ninc\n'*(consequentOnes-1)
    else:
        result+='dbl\ninc\n'*consequentOnes

    # Обрабатываем последние нули
    print(result+'dbl\n'*consequentZeros,end='')
