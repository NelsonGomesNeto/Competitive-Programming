import os
from random import random, randint

mod = int(1e9) + 7

f = open("big", "w")

print(1, file=f)

s = ""
i = 1
res = 1
while len(s) < int(1e5):
    s += str(i) + '*'
    res = res * i % mod
    i += 1
    if i >= 10:
        i = 1
s += str(i)
res = res * i % mod
print(s, file=f)

print(res)

f.close()