import os
from random import randint

os.system("g++ persistentSegmentTree.cpp -o test -std=c++17 -O2")

n = int(1e6)
q = int(1e6)

f = open("big", "w")

print(n, file=f)
a = [randint(0, int(1e9)) for _ in range(n)]
print(*a, file=f)

updates = 0
for _ in range(q):
    op = randint(0, 1)
    if op == 0:
        v, pos = randint(0, updates), randint(0, n - 1)
        value = randint(0, int(1e9))
        print("U", v, pos, value, file=f)
        updates += 1
    if op == 1:
        l = randint(0, n - 2)
        r = randint(l, n - 1)
        v = randint(0, updates)
        print("Q", v, l, r, file=f)

f.close()

os.system("time ./test < big > out")