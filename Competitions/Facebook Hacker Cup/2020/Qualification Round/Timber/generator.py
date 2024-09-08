import os
from random import random, randint

f = open("big", "w")
t = 1
print(t, file=f)
n = int(8e5)
print(n, file=f)
p = set()
while len(p) < n:
    p.add(randint(int(-5e8), int(5e8)))
for i in p:
    print(i, randint(1, 5e8), file=f)
f.close()