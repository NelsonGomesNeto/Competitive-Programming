from random import randint

N = int(1e7)
print(N)
a = [randint(0, int(9)) for _ in range(N)]
print(*a)