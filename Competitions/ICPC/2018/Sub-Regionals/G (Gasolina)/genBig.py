import os
from random import randint, random

f = open("big", "w")

p, r, c = 1000, 1000, 20000
print(p, r, c, file=f)

flowP = []
for i in range(p):
    flowP += [randint(1, 10000)]
print(*flowP, file=f)

flowR = []
for i in range(r):
    flowR += [randint(1, 10000)]
print(*flowR, file=f)

uv = set()
for i in range(c):
    u, v, t = randint(1, p), randint(1, r), randint(1, 1000000)
    while ((u, v) in uv):
        u, v = randint(1, p), randint(1, r)
    uv.add((u, v))
    print(u, v, t, file=f)

f.close()

os.system("time ./test < big")