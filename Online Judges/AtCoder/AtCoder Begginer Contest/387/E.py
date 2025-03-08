import sys
from random import randint
sys.set_int_max_str_digits(0)

def SumDigits(x):
    return sum(map(int, str(x)))

def GoodInteger(x):
    return x % SumDigits(x) == 0

def IsTwin(x):
    return GoodInteger(x) and GoodInteger(x + 1)

def Lol():
    for n in range(int(1e10), int(1e20) + 1):
        ans = -1
        n_str = str(n)
        first_digit = int(n_str[0])
        start = (first_digit + 1) * (10 ** (len(n_str) - 1))
        for i in range(start, 2*n):
            if not IsTwin(i): continue
            ans = i
            break
        if ans == -1:
            print(n, ans)
            break

def Solve():
    n = int(input())
    ans = -1
    if n > 1e8:
        n_str = str(n)
        first_digit = int(n_str[0])
        start = (first_digit + 1) * (10 ** (len(n_str) - 1))
        if 2*n - start < int(1e8):
            start = n
        for i in range(start, 2*n):
            if not IsTwin(i): continue
            ans = i
            break
    else:
        for i in range(n, 2*n):
            if not IsTwin(i): continue
            ans = i
            break
    print(ans)

# Lol()
while True:
    try:
        Solve()
    except EOFError:
        break