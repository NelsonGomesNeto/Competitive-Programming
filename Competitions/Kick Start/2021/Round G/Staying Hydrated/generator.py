import os
from random import random, randint

f = open("big", "w")

t = 5
print(t, file=f)
for tt in range(t):
    k = int(1e5)
    print(k, file=f)
    for i in range(k):
        x0 = randint(int(-1e9), int(1e9) - 1)
        x1 = randint(x0 + 1, int(1e9))
        y0 = randint(int(-1e9), int(1e9) - 1)
        y1 = randint(x0 + 1, int(1e9))
        print(x0, y0, x1, y1, file=f)

f.close()