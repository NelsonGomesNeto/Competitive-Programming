import os
from random import randint

f = open("big", "w")
t = 1
print(t, file=f)
n = 50000
print(n, file=f)
r = [[randint(1, 10) for j in range(5)] for i in range(n)]
for i in range(n):
    print(*r[i], file=f)
f.close()