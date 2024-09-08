import os
from random import random, randint

f = open("big", "w")

t = 1
print(t, file=f)
n = int(5e3)
m = 18
print(n, m, file=f)
s = [''.join(["yn"[randint(0, 1)] for j in range(m)]) for i in range(n)]
for i in range(n):
    print(s[i], file=f)

f.close()