n = int(input())
m = int(input())
a = m // 4 * 2
c = m // 4 * 2
m = m % 4
ost = m * 2 + n
if ost >= 8:
    a += ost // 4
    c += ost // 4
    n = ost % 4
    m = 0
elif m > 0:
    if m >= 2:
        a += 2
    elif n >= 2: # m == 1
        a += 2
        b += 2
        n -= 2
elif n >= 4: # m == 0
    a += 1
    c += 1
    n -= 4
if n >= 2:
    c += 1

print(a * c)