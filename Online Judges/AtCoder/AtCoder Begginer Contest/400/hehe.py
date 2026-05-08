from random import randint


n = 50
print(n)
c = [randint(1, n) for _ in range(n)]
print(*c)
x = [randint(1, int(1e9)) for _ in range(n)]
print(*x)