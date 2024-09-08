import os
from random import random, randint

f = open("big", "w")

t = 100
for tt in range(t):
    print(t, file=f)
    k = int(1e4)
    n = int(5e3) if tt < 25 else int(5e2)
    print(n, k, file=f)
    b = [randint(0, k) for _ in range(k)]
    print(*b, file=f)

f.close()