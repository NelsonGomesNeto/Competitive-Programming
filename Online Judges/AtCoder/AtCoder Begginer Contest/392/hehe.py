from random import randint

n = int(5e5)
a = [randint(1, i) for i in range(1, n + 1)]
print(n)
print(*a)