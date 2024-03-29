"""
Задание связано с обратной польской нотацией. Она используется для парсинга арифметических выражений. Ещё её иногда называют постфиксной нотацией. В постфиксной нотации операнды расположены перед знаками операций.

Формат ввода
В единственной строке дано выражение, записанное в обратной польской нотации. Числа и арифметические операции записаны через пробел.
На вход могут подаваться операции: +, -, *, / и числа, по модулю не превосходящие 10000.
Операция / является математическим целочисленным делением с округлением вниз.
Гарантируется, что значение промежуточных выражений в тестовых данных по модулю не больше 50000.

Формат вывода
Выведите единственное число - значение выражения

Примеры
3 4 +
7

12 5 /
2

-1 3 /
-1

10 2 4 * -
2

2 1 + 3 *
9

7 2 + 4 * 2 +
38

"""
class CustomNoItemsException(Exception):
    def __init__(self):
        pass

class Stack:
    def __init__(self):
        self.__data=[]
        
    def push(self,element):
        self.__data.append(element)
    
    def pop(self):
        if len(self.__data)==0:
            raise CustomNoItemsException
        else:
            return self.__data.pop()

def calculate(input_string):
    dictionary={
    '+':lambda x,y:x+y,
    '-':lambda x,y:y-x,
    '*':lambda x,y:x*y,
    '/':lambda x,y:y//x
    }
    operands = Stack()
    for val in input_string.split(' '):
        try:
            operands.push(int(val))
        except ValueError:
            operands.push(dictionary[val](operands.pop(),operands.pop()))
    
    return operands.pop()


print(calculate(input()))
