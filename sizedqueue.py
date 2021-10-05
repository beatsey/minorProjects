"""
Ограниченная очередь

Нужно написать класс MyQueueSized, который принимает параметр max_size, означающий максимально допустимое количество элементов в очереди.
Реализуйте программу, которая будет эмулировать работу такой очереди.
Функции, которые надо реализовать, описаны в формате ввода.

Формат ввода
В первой строке записано одно число - количество команд, оно не превосходит 5000. Во второй строке задан максимально допустимый размер очереди, он не превосходит 5000. Далее идут команды по одной на строке. Команды могут быть следующих видов:
* push(x) - добавить число x в очередь;
* pop() - удалить число из очереди и вывести на печать;
* peek() - напечатать первое число в очереди;
* size() - вернуть размер очереди.

При превышении допустимого размера очереди нужно вывести "error". При вызове операций pop() или peek() для пустой очереди нужно вывести "None".

Формат вывода
Напечатайте результаты выполнения нужных команд, по одному на строке.

Примеры
8
2
peek
push 5
push 2
peek
size
size
push 1
size

None
5
2
2
error
2


10
1
push 1
size
push 3
size
push 1
pop
push 1
pop
push 3
push 3

1
error
1
error
1
1
error
"""

class CustomNoItemsException(Exception):
    def __init__(self):
        pass
        
class CustomOverflowException(Exception):
    def __init__(self):
        pass

class MyQueueSized:
    def __init__(self,max_size):
        self.__array = [None]*max_size # Список, реализующий очередь
        self.__max_size = max_size
        self.__head=0 # Индекс начала
        self.__tail=-1 # Индекс конца
        self.__size=0 # Размер очереди
    
    def push(self,element):
        if self.__size != self.__max_size: # Если есть место
            self.__tail = (self.__tail + 1) % self.__max_size
            self.__array[self.__tail]=element # то записываем новый элемент в конец
            self.__size += 1
        else:
            raise CustomOverflowException
    
    def size(self):
        return self.__size
    
    def peek(self):
        if self.__size == 0:
            raise CustomNoItemsException
        else:
            return self.__array[self.__head]
    
    def pop(self):
        x=self.peek()
        self.__head = (self.__head + 1) % self.__max_size
        self.__size -= 1
        return x

n=int(input())
max_size=int(input())
sizedQueue=MyQueueSized(max_size)
for i in range(n):
    try:
        command = input().split(' ')
        if(len(command)==1):
            print(getattr(sizedQueue,command[0])())
        else:
            getattr(sizedQueue,command[0])(int(command[1]))
    except CustomOverflowException:
        print('error')
    except CustomNoItemsException:
        print('None')