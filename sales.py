"""
Продажи

Дана база данных о продажах некоторого интернет-магазина. Каждая строка входного файла представляет собой запись вида Покупатель товар количество, где Покупатель — имя покупателя (строка без пробелов), товар — название товара (строка без пробелов), количество — количество приобретенных единиц товара. Создайте список всех покупателей, а для каждого покупателя подсчитайте количество приобретенных им единиц каждого вида товаров.

Формат ввода
Вводятся сведения о покупках в указанном формате.

Формат вывода
Выведите список всех покупателей в лексикографическом порядке, после имени каждого покупателя выведите двоеточие, затем выведите список названий всех приобретенных данным покупателем товаров в лексикографическом порядке, после названия каждого товара выведите количество единиц товара, приобретенных данным покупателем. Информация о каждом товаре выводится в отдельной строке.


Пример 1
Ввод
Ivanov paper 10
Petrov pens 5
Ivanov marker 3
Ivanov paper 7
Petrov envelope 20
Ivanov envelope 5

Вывод
Ivanov:
envelope 5
marker 3
paper 17
Petrov:
envelope 20
pens 5


Пример 2
Ввод
Ivanov aaa 1
Petrov aaa 2
Sidorov aaa 3
Ivanov aaa 6
Petrov aaa 7
Sidorov aaa 8
Ivanov bbb 3
Petrov bbb 7
Sidorov aaa 345
Ivanov ccc 45
Petrov ddd 34
Ziborov eee 234
Ivanov aaa 45

Вывод
Ivanov:
aaa 52
bbb 3
ccc 45
Petrov:
aaa 9
bbb 7
ddd 34
Sidorov:
aaa 356
Ziborov:
eee 234
"""

dictionary={}

with open('input.txt') as f:
    lines = f.read().split('\n')
    
    for line in lines:
        inp = line.split(' ')
        username = inp[0]
        productname = inp[1]
        quantity = int(inp[2])
        if username not in dictionary:
            dictionary[username]={}
            
        if productname in dictionary[username]:
            dictionary[username][productname]+=quantity
        else:
            dictionary[username][productname]=quantity

for user in sorted(dictionary):
    print(user+':')
    
    for item in sorted(dictionary[user]):
        print(item+' '+str(dictionary[user][item]))