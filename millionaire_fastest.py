"""
Суть алгоритма заключается в том, что мы рассматриваем задачу с точки зрения построения заданного двоичного числа из 0 с помощью операций сдвига влево (dbl), +1 (inc) и -1 (dec).
Для N подряд идущих единиц оптимальной стратегией будет inc dbl (N раз) dec, когда N>=3. Или (inc dbl) (N раз) для 0<N<3.
Но есть исключения. Например для последовательности 111011 оптимальной стратегией будет inc dbl dbl dbl dbl dec dbl dbl dec.
То есть на оптимальную стратегию получения последовательности единиц влияет предшествующие биты. Поэтому и возникает столько много ситуаций.

Вычислительная сложность O(N), где N - длина двоичной записи исходного числа.
Сложность по памяти O(1). Т.е. дополнительной памяти для работы алгоритма не требуется.
Реализация эффективнее, чем O(N) невозможна, т.к. для точного решения требуется пройти каждый бит числа хотя бы раз.
"""
def printBestSequence(target):
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
            if consequentZeros == 1:
                # Один ноль между последовательностями => Продолжаем
                print('dbl\n' * (consequentOnes + 1),end="")
                print('dec')
                
                consequentZeros = 0
                consequentOnes = 1
                continue
            else:
                # Заканчиваем последовательность
                print('dbl\n' * consequentOnes,end="")
                print('dec')
                flagDecDblSequence = False
        else:
            if consequentOnes >= 3:
                print('inc')
                flagLeadOne = False
                if consequentZeros == 1:
                    print('dbl\n'*(consequentOnes+1),end="")
                    print('dec')
                    flagDecDblSequence = True
                    
                    consequentZeros = 0
                    consequentOnes = 1
                    continue
                else:
                    print('dbl\n'*consequentOnes,end="")
                    print('dec')
            elif flagLeadOne:
                if consequentOnes == 2:
                    print('inc\ndbl\ninc')
                else:
                    print('inc')
                flagLeadOne = False
            else:
                if (consequentOnes == 2) and (consequentZeros==1):
                    flagDecDblSequence = True
                    print('inc','dbl','dbl','dbl','dec',sep="\n")
                    
                    consequentOnes = 1
                    consequentZeros = 0
                    continue;
                else:
                    print('dbl\ninc\n'*consequentOnes,end='')

        print('dbl\n'*consequentZeros,end='')

        consequentOnes = 1
        consequentZeros = 0
    #end for
    
    # Обрабатываем последние 1..10..0
    if flagDecDblSequence:
        print('dbl\n' * consequentOnes,end="")
        print('dec')
    else:
        if consequentOnes >= 3:
            print('inc')
            print('dbl\n'*consequentOnes,end="")
            print('dec')
        elif flagLeadOne:
            if consequentOnes == 2:
                print('inc\ndbl\ninc')
            else:
                print('inc')
        else:
            print('dbl\ninc\n'*consequentOnes,end='')
           
    # Обрабатываем последние нули
    if consequentZeros!=0:
        print('dbl\n'*consequentZeros,end='')

printBestSequence(int(input()))
