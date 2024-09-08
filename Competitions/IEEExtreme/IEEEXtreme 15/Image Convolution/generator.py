import os
from random import random, randint

f = open("big", "w")
print(1, file=f)
n, m = 500, 500
print(n, m, file=f)
for i in range(n):
    print(''.join([".#"[randint(0, 1)] for j in range(m)]), file=f)
a, b = 200, 200
print(a, b, file=f)
for i in range(a):
    print(''.join([".#?"[randint(0, 2)] for j in range(b)]), file=f)
f.close()