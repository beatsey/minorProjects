"""
Суть алгоритма заключается в том, что мы рассматриваем задачу с точки зрения построения заданного двоичного числа из 0 с помощью операций сдвига влево (dbl), +1 (inc) и -1 (dec).
Для N подряд идущих единиц оптимальной стратегией будет inc dbl (N раз) dec, когда N>=3. Или (inc dbl) (N раз) для 0<N<3.
Но есть исключения. Например для последовательности 111011 оптимальной стратегией будет inc dbl dbl dbl dbl dec dbl dbl dec.
То есть на оптимальную стратегию получения последовательности единиц влияет предшествующие биты. Поэтому и возникает столько много ситуаций.

Вычислительная сложность O(N), где N - длина двоичной записи исходного числа.
Сложность по памяти O(1). Т.е. дополнительной памяти для работы алгоритма не требуется.
Реализация эффективнее, чем O(N) невозможна, т.к. для точного решения требуется пройти каждый бит числа хотя бы раз.
"""
def printBestSequenceRefactored(target):
    if target <=0:
        return

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
            print('dbl\n' * consequentOnes,end='')
            if consequentZeros == 1:
                print('dbl\ndec',sep='')
            else:
                flagDecDblSequence = False
                print('dec\n','dbl\n' * consequentZeros,sep='',end='')

        elif consequentOnes >= 3:
            print('inc\n','dbl\n' * consequentOnes,sep='',end='')
            flagLeadOne = False

            if consequentZeros == 1:
                flagDecDblSequence = True
                print('dbl\ndec',sep='')
            else:
                print('dec\n','dbl\n' * consequentZeros,sep='',end='')

        elif flagLeadOne:
            print('inc\ndbl\n'*consequentOnes,'dbl\n'*(consequentZeros-1),sep='',end='')
            flagLeadOne = False
        elif consequentOnes == 2 and consequentZeros == 1:
            flagDecDblSequence = True
            print('inc\ndbl\ndbl\ndbl\ndec\n',sep='',end='')
        else:
            print('dbl\ninc\n'*consequentOnes,'dbl\n'*consequentZeros,sep='',end='')

        consequentZeros = 0
        consequentOnes = 1
    #end for

    # Обрабатываем последние 1..10..0
    if flagDecDblSequence:
        print('dbl\n' * consequentOnes,'dec\n',sep='',end='')
    elif consequentOnes >= 3:
        print('inc\n','dbl\n' * consequentOnes,'dec\n',sep='',end='')
    elif flagLeadOne:
        print('inc\n','dbl\ninc\n'*(consequentOnes-1),sep='',end='')
    else:
        print('dbl\ninc\n'*consequentOnes,sep='',end='')

    # Обрабатываем последние нули
    print('dbl\n'*consequentZeros,sep='',end='')
printBestSequenceRefactored(int(input()))
