M, K = [int(X) for X in input().split(' ')]

spheres=[]
pallelepiped=[]

for i in range(M):
    sphere = [int(j) for j in input().split(' ')]
    sphere.append(False)
    spheres.append(sphere)

for i in range(K):
    pallelepiped = [int(j) for j in input().split(' ')]

    X = pallelepiped[0::3]
    Y = pallelepiped[1::3]
    Z = pallelepiped[2::3]

    X0, X1 = min(X),max(X)
    Y0, Y1 = min(Y),max(Y)
    Z0, Z1 = min(Z),max(Z)

    for sphere in spheres:
        X,Y,Z,R,dirty = sphere
        if dirty:
            continue
        if X-R<X0 or Y-R<Y0 or Z-R<Z0 or X+R>X1 or Y+R>Y1 or Z+R>Z1:
            sphere[4] = True

for i in range(len(spheres)):
    if spheres[i][4]:
        print(i+1)

"""
2 1
1 1 1 1
10 10 10 2
0 0 0 10 0 0 0 10 0 10 10 0 0 0 10 10 0 10 0 10 10 10 10 10

"""