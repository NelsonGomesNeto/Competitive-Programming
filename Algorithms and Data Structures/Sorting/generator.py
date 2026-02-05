from random import randint

N = int(1e3)
print(N)
a = [randint(0, N) for _ in range(N)]
print(*a)