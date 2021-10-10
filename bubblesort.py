n=int(input())
array=input().split(' ')

somethingChanged = True
flag = False

while somethingChanged:
    if flag:
        print(' '.join(array))
  
    flag = True  
    somethingChanged = False
    for i in range(n-1):
        if int(array[i])>int(array[i+1]):
            array[i],array[i+1]=array[i+1],array[i]
            somethingChanged = True