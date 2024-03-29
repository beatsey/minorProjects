"""
Рита по поручению Тимофея наводит порядок в правильных скобочных последовательностях (ПСП), состоящих только из круглых скобок (). Для этого ей надо сгенерировать все ПСП длины 2n в алфавитном порядке - алфавит состоит из ( и ) и открывающаяся скобка идёт раньше закрывающей. Помогите Рите - напишите программу, которая по заданному n выведет все ПСП в нужном порядке.

Рассмотрим второй пример. Надо вывести ПСП из четырёх символов. Таких всего две:
1. (())
2. ()()

(()) идёт раньше ()(), так как первый символ у них одинаковый, а на второй позиции у первой ПСП стоит (, который идёт раньше ).

Формат ввода
На вход функция принимает n - целое число от 0 до 10.

Формат вывода
Функция должна напечатать все возможные скобочные последовательности заданной длины в алфавитном (лексикографическом) порядке.

Примеры
3

((()))
(()())
(())()
()(())
()()()


2

(())
()()


4

(((())))
((()()))
((())())
((()))()
(()(()))
(()()())
(()())()
(())(())
(())()()
()((()))
()(()())
()(())()
()()(())
()()()()
"""

d={}

def generator(n):
    def getGen(k):
        if k not in d:
            d[k]=generator(k)
        return d[k]
    
    if n<=0:
        return set([''])
    
    newData=set()
    for i in getGen(n-1):
        newData.add('('+i+')')
        newData.add(i+'()')
        newData.add('()'+i)
    
    for j in range(2,n//2+1):
        b=getGen(j)
        for i in getGen(n-j):
            for k in b:
                newData.add(i+k)
                newData.add(k+i)
    
    return newData

n=int(input())
print('\n'.join(sorted(generator(n))),end='')

"""
Аналогичная задача на leetcode:
https://leetcode.com/problems/generate-parentheses/
Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.
Example 1:
Input: n = 3
Output: ["((()))","(()())","(())()","()(())","()()()"]

Example 2:
Input: n = 1
Output: ["()"]
 
Constraints:
1 <= n <= 8
"""

def generateParenthesis(n):
    def gen(n, open_brackets, prefix, llist):
        if n==1:
            llist.append(prefix+')')
            return

        if n>open_brackets:
            gen(n-1, open_brackets+1, prefix+'(', llist)

        if open_brackets>0:
            gen(n-1, open_brackets-1, prefix+')', llist)

    llist = []
    gen(2 * n, 0, '', llist)
    return llist
# print(generateParenthesis(n))
