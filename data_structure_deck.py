"""
Гоша реализовал структуру данных Дек, максимальный размер которого определяется заданным числом. Методы push_back(x), push_front(x), pop_back(), pop_front() работали корректно. Но, если в деке было много элементов, программа работала очень долго. Дело в том, что не все операции выполнялись за О(1). Помогите Гоше написать эффективную реализацию. При реализации нельзя использовать связный список.

Формат ввода
В первой строке записано количество команд n - целое число, не превосходящее 5000. Во второй строке записано число m - максимальный размер дека. Он не превосходит 1000. В следующих n строках записана одна из команд:
* push_back(value) - добавить элемент в конец дека. Если в деке уже находится максимальное число элементов, вывести 'error'.
* push_front(value) - добавить элемент в начало дека. Если в деке уже находится максимальное число элементов, вывести 'error'.
* pop_back() - вывести последний элемент дека и удалить его. Если дек был пуст, то вывести 'error'.
* pop_front() - вывести первый элемент дека и удалить его. Если дек был пуст, то вывести 'error'.
Value - целое число, по модулю не превосходящее 1000

Формат вывода
Выведите результат выполнения кадой команды на отдельной строке. Для успешных запросов push_back(x) и push_front(x) ничего выводить не надо.

Примеры
4
4
push_front 861
push_front -819
pop_back
pop_back

861
-819


7
10
push_front -855
push_front 720
pop_back
pop_back
push_back 844
pop_back
push_back 823

-855
720
844
"""
class MyError(Exception):
    def __init__(self):
        pass

class Deck:
    def __init__(self,max_n):
        self.__array = [None]*max_n # Список, реализующий Дек
        self.__max_n=max_n # Максимальный размер
        self.__head=0 # Индекс начала Дека
        self.__tail=-1 # Индекс конца Дека
        self.__size=0 # Размер очереди
    def is_empty(self):
        return self.__size == 0
    
    def push_back(self,element):
        if self.__size != self.__max_n: # Если есть место
            self.__tail = (self.__tail + 1) % self.__max_n
            self.__array[self.__tail]=element # то записываем новый элемент в конец
            self.__size += 1
        else:
            raise MyError
            
    def pop_back(self):
        if self.is_empty(): # Если дек пуст, то ошибка
            raise MyError
        else:
            print(self.__array[self.__tail])
            self.__tail = (self.__tail - 1) % self.__max_n # сдвигаем хвост на последний элемент
            self.__size -= 1
    
    def push_front(self,element):
        if self.__size != self.__max_n: # Если есть место
            self.__head = (self.__head - 1) % self.__max_n # то добавляем новый элемент в начало
            self.__array[self.__head] = element
            self.__size += 1
        else:
            raise MyError
    
    def pop_front(self):
        if self.is_empty():
            raise MyError
        else:
            print(self.__array[self.__head])
            self.__head = (self.__head + 1) % self.__max_n
            self.__size -= 1

n=int(input()) # количество команд
m=int(input()) # размер Дека
deck = Deck(m) # создаём Дек
for i in range(n):
    try:
        command = input().split(' ')
        if(len(command)==1):
            getattr(deck,command[0])()
        else:
            getattr(deck,command[0])(command[1])
    except MyError:
        print('error')