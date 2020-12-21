# Номер 2
inpArray=input().split(' ')
countSystemBase, lastDigit, power = int(inpArray[0]), inpArray[1][-1].upper(), int(inpArray[2])

if('0'<lastDigit and lastDigit<='9'):
    lastDigit = int(lastDigit)
else:
    lastDigit = 10 + ord(lastDigit) - ord('A')

result = lastDigit
for i in range(power-1):
    result = result*lastDigit%countSystemBase

if(result<10):
    print(result)
else:
    print(chr(ord('A')+result-10))