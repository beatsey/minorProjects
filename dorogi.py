'''
Движение по полосам
При организации движения по сложным перекресткам, для того, чтобы траектории водителей, выполняющих различные маневры,
не пересекались, вводят ограничения на возможные маневры водителей, в зависимости от того, по какой полосе движения водитель подъехал к перекрестку.
Для этого используется знак "движение по полосам".
Рассмотрим дорогу, подходящую к перекрестку, на котором сходится m дорог.
Водитель, подъезжающий к перекрестку по этой дороге, потенциально может продолжить свое движение в m различных направлениях - обратно по дороге, по которой он приехал,
а также по одной из оставшихся m - 1 дорог. Пронумеруем возможные направления числами от 1 до m слева направо с точки зрения подъезжающего водителя.
Номер 1 получит разворот и возврат по дороге, по которой водитель подъезжал к перекрестку, номер 2 - поворот на самую левую из дорог, и т.д.

Пусть дорога содержит n полос для движения.
Пронумеруем полосы от 1 до n слева направо, самая левая полоса получит номер 1, следующая номер 2, и т.д.
Знак "движение по полосам" разрешает каждой из полос движение по некоторым из m возможных направлений.
При этом должны выполняться следующие условия:
1. Если с i-й полосы разрешено движение в a-м направлении, а с j-й полосы разрешено в b-м направлении, причём i < j, то a <= b.
2. С каждой полосы разрешено движение хотя бы в одном направлении.
3. В каждом направлении разрешено движение хотя бы с одной полосы.

Инспекция по безопасности дорожного движения заинтересовалась, а сколько различных знаков "движение по полосам" можно установить перед таким перекрестком.
Помогите им найти ответ на этот вопрос.

Формат ввода
Два целых числа: m и n (2<=m<=50, 1<=n<=15).
m - число дорог, n - число полос

Формат вывода
В выходной файл выведите одно число - количество возможных знаков "движение по полосам", которые можно установить перед перекрестком.

'''

m, n = map(int, input().split())

costs = [1] * (m + 1)
costs[0] = 0

for _ in range(n-1):
    cpy = costs.copy()

    for k in range(1, m + 1):
        costs[k] = 0
        for i in range(k):
            costs[k] += cpy[i] + cpy[i+1]

print(costs[-1])

# recursive way
'''
def f(m, n):
    if m == 0:
        return 0
    if n == 1:
        return 1
    s = 0
    # Цикл по всем возможным направлениям из левой полосы
    # Например, если i=4, то из левой полосы можно повернуть в направления 0,1,2,3,4
    # В полосе правее можно повернуть в направления i, i+1, i+2, ..., m
    for i in range(m):
        s += f(m - i, n - 1) + f(m - i - 1, n - 1)
    return s

print(f(m, n))
'''
