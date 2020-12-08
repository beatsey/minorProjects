"""
Автокоррекция
Реализуйте программу, которая предлагает варианты замены слова, в котором допущена одна ошибка.
Эту задачу можно решить достаточно многими способами - на это ограничений нет, но код должен быть хорошего качества и читаемым.
Регистр букв для программы коррекции не имеет значения (слова в словаре хранятся в нижнем регистре).
Варианты ошибок - как в алгоритме Дамерау-Левенштейна: вставка лишнего символа, удаление символа, замена символа или транспозиция соседних символов.

Формат входных данных
Данные подаются на стандартный поток ввода. Пустые строки игнорируются.
Первая строка содержит число N - количество слов в словаре.
Последующие N строк содержат слова из словаря, по одному в строке.
Остальные строки - слова, которые надо проверять.

Формат результата
Каждая строка выхода содержит предложение для исправления слов, в порядке их появления.
Если слово не содержит ошибок, то выводится "%слово% - ok".
Если слово содержит одну ошибку, то выводится "%слово% -> %слово_в_словаре%". Если вариантов несколько, то они разделяются запятой с пробелом.
Если слово содержит более одной ошибки, то выводится "%слово% -?"
Результат работы программы выводится в стандартный поток вывода.

Примеры
Входные данные
8
some
random
words
for
testing
your
solutions
far

some
randoms
wards
seeking
fro
solution
fur

Результат работы
some - ok
randoms -> random
wards -> words
seeking -?
fro -> for
solution -> solutions
fur -> far, for

"""

#независимое от реализации класса с алгоритмом чтение словаря
def readDictionary():
    N = int(input())
    dict = {}
    for i in range(N):
        word = input().lower()
        length = len(word)
        
        if length not in dict:
            dict[length] = {word:True}
        else:
            dict[length][word] = True
    return dict

# реализация алгоритма
def correctWord(word,dict):

    def isOneCharDiffOrTranspose(word1,word2):
        counter = 0
        transposeFlag = False
        for i in range(len(word1)):
            if word1[i]!=word2[i]:
                counter = counter + 1
                if counter==3:
                    return False
                if counter==2:
                    if transposeFlag:
                        # Предыдущая ошибка была на символ ранее
                        # Проверяем, может быть это транспозиция
                        if word1[i-1]==word2[i] and word1[i]==word2[i-1]:
                            continue
                    
                    return False
                transposeFlag = True
            else:
                transposeFlag = False
        return True

    def isOneCharInsertionDiff(shorter,longer):
        diffCounter = 0
        N = len(shorter)
        i=0
        while i<N:
            if shorter[i] != longer[i+diffCounter]:
                diffCounter = diffCounter + 1
                if diffCounter == 2:
                    return False
            else:
                i = i + 1
        return True


    wordLower = word.lower()
    length = len(word)
    lengthInDict = length in dict
    if lengthInDict and wordLower in dict[length]:
        return True

    result = []

    if length-1 in dict:
        for w in dict[length-1]:
            if isOneCharInsertionDiff(w,wordLower):
                result.append(w)

    if lengthInDict:
        for w in dict[length]:
            if isOneCharDiffOrTranspose(wordLower,w):
                result.append(w)

    if length+1 in dict:
        for w in dict[length+1]:
            if isOneCharInsertionDiff(wordLower,w):
                result.append(w)

    result.sort()
    return result

# вывод результата корректировки слова в нужном формате
def printableResult(res,word):
    if res==True:
        return '{} - ok'.format(word)
    elif res:
        return '{} -> {}'.format(word,', '.join(res))
    else:
        return '{} -?'.format(word)

#независимое от реализации алгоритма чтение ввода
def processWordsFromInput(dict):
    while True:
        try:
            word = input()
        except EOFError:
            break
        except KeyboardInterrupt:
            break
        
        if (len(word)!=0):
            result = correctWord(word,dict)
            print(printableResult(result,word))

dict = readDictionary()
processWordsFromInput(dict)
