"""
Списочная очередь

Любимый вариант очереди Тимофея - очередь, написанная с использованием связного списка. Помогите ему с реализацией. Очередь должна поддерживать выполнение трёх команд:
* get() - вывести элемент, находящийся в голове очереди, и удалить его. Если очередь пуста, то вывести "error";
* put(x) - добавить число x в очередь;
* size() - вывести текущий размер очереди.

Формат ввода
В первой строке записано количество команд n - целое число, не превосходящее 1000. В каждой из следующих n строк записаны команды по одной строке.

Формат вывода
Напечатайте результаты выполнения нужных команд, по одному на строке.

Примеры
10
put -34
put -23
get
size
get
size
get
get
put 80
size

-34
1
-23
0
error
error
1


6
put -66
put 98
size
size
get
get

2
2
-66
98


9
get
size
put 74
get
size
put 90
size
size
size

error
0
74
0
1
1
1
"""

class CustomNoItemsException(Exception):
    def __init__(self):
        pass

class QueueUsingList:
    def __init__(self):
        self.__array = [] # Список, реализующий очередь
    
    def put(self,element):
        self.__array.append(element)
    
    def size(self):
        return len(self.__array)
    
    def get(self):
        if self.size() == 0:
            raise CustomNoItemsException
        else:
            return self.__array.pop(0)

n=int(input())
queueUsingList=QueueUsingList()
for i in range(n):
    try:
        command = input().split(' ')
        if(len(command)==1):
            print(getattr(queueUsingList,command[0])())
        else:
            getattr(queueUsingList,command[0])(command[1])
    except CustomNoItemsException:
        print('error')