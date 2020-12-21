# Номер 1
maxLength, M = [int(X) for X in input().split(' ')]
needPparts = 0

for i in range(M):
    N = int(input())
    division = N//maxLength

    if(N%maxLength==0):
        division-=1
    needPparts+=division

print(needPparts)
