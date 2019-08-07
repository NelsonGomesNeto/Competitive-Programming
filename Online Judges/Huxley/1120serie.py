from math import sqrt

def fatorial(n):
    if (n <= 1):
        return(1)
    return(n * fatorial(n - 1))

def serie(i, n, suma):
    now = fatorial(i)/sqrt(2*i + 1)
    suma += now
    if (i == n):
        print("S: %.12Lf" % suma)
        return
    serie(i + 1, n, suma)
    print("%.12Lf" % now)

n = int(input())
serie(1, n, 0)