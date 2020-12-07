def reducted(size):
    if (size % 4 == 1):
        return(0)
    if (size % 4 == 0):
        return(3)
    if (size % 4 == 2):
        return(1)
    if (size % 4 == 3):
        return(2)

def reduction(a, size):
    times, k = reducted(size), 1
    for i in range(0, times):
        for j in range(0, size - i - 1):
            a[j] = (a[j] + (k * a[j + 1]))
            if (a[j] < 0):
                a[j] += 1000000007
            a[j] %= 1000000007
            k *= -1

def binomial(n, k):
    if k < 0 or k > n:
        return 0
    if k == 0 or k == n:
        return 1
    k = min(k, n - k) # take advantage of symmetry
    c = 1
    for i in range(k):
        c = c * (n - i) / (i + 1)
    return c

def doSum(a, size):
    suma, k = 0, 0
    pot = int((size - 1) / 2)
    for i in range(0, size, 2):
        j = int(binomial(pot, k))
        suma += (j * a[i]) % 1000000007
        if (suma < 0):
            suma += 1000000007
        suma %= 1000000007
        k += 1

    if (suma < 0):
        suma += 1000000007

    return(suma % 1000000007)

size = int(input())
a = list(map(int, input().split())) # Lê uma lista em uma linha
reduction(a, size)
print(int(doSum(a, size - reducted(size))))
