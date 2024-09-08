import os
from random import random, randint

f = open("big", "w")

max_n = int(3e5)
max_x = int(1e5)
y, n = max_n, max_n
print(y, n, file=f)
x = [randint(0, 1) for _ in range(y)]
print(*x, file=f)
for i in range(n):
    a = randint(1, y)
    p = max_x
    ff = randint(0, y - a)
    print(a, p, ff, file=f)

f.close()