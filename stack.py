"""
Стек

Нужно реализовать класс StackMax, который поддерживает операцию определения максимума среди всех элементов в стеке. Класс должен поддерживать операции push(x), где x - целое число, pop() и get_max().

Формат ввода
В первой строке записано одно число n - количество команд, которое не превосходит 10000. В следующих n строках идут команды. Команды могут быть следующих видов:
* push(x) - обавить число x в стек;
* pop() - удалить число с вершины стека;
* get_max() - напечатать максимальное число в стеке

Если стек пуст, при вызове команды get_max() нужно напечатать "None", для команды pop() - "error".

Формат вывода
Для каждой команды get_max() напечатайте результат её выполнения. Если стек пустой, для команды get_max() напечатайте "None". Если происходит удаление из пустого стека - напечатайте "error".

Примеры
8
get_max
push 7
pop
push -2
push -1
pop
get_max
get_max

None
-2
-2

7
get_max
pop
pop
pop
push 10
get_max
push -9

None
error
error
error
10
"""
class CustomNoItemsException(Exception):
    def __init__(self):
        pass

class StackMax:
    def __init__(self):
        self.__data=[]
        
    def push(self,element):
        self.__data.append(element)
    
    def pop(self):
        if len(self.__data)==0:
            raise CustomNoItemsException
        else:
            return self.__data.pop()
    
    def get_max(self):
        try:
            return max(self.__data)
        except:
            return 'None'

n=int(input())
stack=StackMax()
for i in range(n):
    try:
        command = input().split(' ')
        if(len(command)==1):
            if command[0]=='pop':
                stack.pop()
            elif command[0]=='get_max':
                print(stack.get_max())
        else:
            getattr(stack,command[0])(int(command[1]))
    except CustomNoItemsException:
        print('error')