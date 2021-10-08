"""
Комбинации (combinations_mobile.py)

На клавиатуре старых мобильных телефонов каждой цифре соответствовало несколько букв. Примерно так:
2: 'abc'
3: 'def'
4: 'ghi'
5: 'jkl'
6: 'mno'
7: 'pqrs'
8: 'tuv'
9: 'wxyz'

Вам известно в каком порядке были нажаты кнопки телефона, без учёта повторов. Напечатайте все комбинации букв, которые можно набрать такой последовательностью нажатий.

Формат ввода
На вход подаётся строка, состоящая из цифр 2-9 включительно. Длина строки не превосходит 10 символов.

Формат вывода
Выведите все возможные комбинации букв через пробел.

Примеры
23

ad ae af bd be bf cd ce cf


92
wa wb wc xa xb xc ya yb yc za zb zc
"""

def combinations(input_string):
    d={ '2': 'abc',
        '3': 'def',
        '4': 'ghi',
        '5': 'jkl',
        '6': 'mno',
        '7': 'pqrs',
        '8': 'tuv',
        '9': 'wxyz' }
    
    if input_string=='':
        return ['']
    
    data = []
    word = d[input_string[-1]]
    
    for combination in combinations(input_string[:-1:]):
        for c in word:
            data.append(combination+c)
    
    return data

print(' '.join(combinations(input())))