
# Номер 3

def func():
    volume, M = [int(X) for X in input().split(' ')]

    sortedVolumes=[]

    for i in range(1,M+1):
        V = float(input())
        if(volume-V>=0):
            sortedVolumes.append((V,i))
            volume-=V
        else:
            sortedVolumes.sort(key=lambda x:x[0])
            if sortedVolumes[0][0]<V:
                volume=volume+sortedVolumes[0][0]-V
                sortedVolumes[0]=(V,i)

    if len(sortedVolumes)==0:
        print('NO')
        return

    # Удаляем лишние кастрюли
    sortedVolumes.sort(key=lambda x:x[0])

    for i in range(len(sortedVolumes)):
        volume += sortedVolumes[i][0]
        if(volume>0):
            index=i
            break

    # Выводим индексы всех предметов начиная с index
    sortedVolumes=sortedVolumes[index::]
    sortedVolumes.sort(key=lambda x:x[1])

    out=''
    for i in range(len(sortedVolumes)):
        out+='{}\n'.format(sortedVolumes[i][1])
    print(out)

func()