"""
Регистрация
Предварительно создайте текстовый файл (accounts.txt), в котором структурирована информация вида: login -> password (не менее 5 пар). При этом на каждой строчке содержатся уникальные логины, а пароли могут повторяться. Создайте функцию регистрации нового пользователя, которая будет предлагать пользователю ввести логин и пароль до тех пор, пока не будет введён уникальный логин, и пароль не будет соответствовать требованиям:
* Наличие букв в разных регистрах
* Наличие цифры
* Наличие спецсимвола (@,!,$,#)

Корректная комбинация должна быть добавлена в текстовый файл accounts.txt.


Contents of accounts.txt:
login1 -> password
user -> friendly
summer -> qwerty
qbq812309 -> gdhjasdgj
nagibator228 -> systemCall1238sj
newUser -> Hey2201#

"""


def readLogins():
    f = open('accounts.txt', 'r')
    logins = {line.strip().partition(' -> ')[0] for line in f}
    f.close()
    return logins
def verifyPassword(password):
    lowerCase=False
    upperCase=False
    containsNumber=False
    containsSpecSymbol=False
    
    for c in password:
        if c.islower():
            lowerCase=True
        elif c.isupper():
            upperCase=True
        elif c.isdigit():
            containsNumber=True
        elif (c=='@') or (c=='!') or (c=='$') or (c=='#'):
            containsSpecSymbol=True
    return lowerCase and upperCase and containsNumber and containsSpecSymbol

def register():
    accounts=readLogins()
    
    while True:
        login = input('Provide login:')
        if login in accounts:
            print('This login is already in use. Please, provide another one.')
            continue
        
        password = input('Provide password:')
        
        if verifyPassword(password):
            f = open('accounts.txt', 'a')
            f.write('{} -> {}\n'.format(login,password))
            f.close()
            print('Account sucessfully registered')
            return True
        else:
            print('Please, provide correct password. Password should:',
                  '* contain a number',
                  '* contain !,@,$ or # symbol',
                  '* contain a lowercase letter',
                  '* contain an uppercase letter',sep='\n',end='\n\n')

register()