from random import randint


n = int(1e6)
k = int(1e6)
a = [randint(1, n) for i in range(n)]
print(n, k)
print(*a)