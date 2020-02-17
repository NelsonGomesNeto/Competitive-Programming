import os
import time
from random import random, randint
os.system("g++ ./../D.cpp -o ./../test")

testCases = int(input())
maxTime = 0
for t in range(1, testCases + 1):
    f = open("%d.in" % t, "w")
    n, m = randint(int(1), int(2e3)), randint(int(1), int(2e3))
    print(n, m, file=f)
    a = [randint(0, int(1e9)) for i in range(n)]
    print(*a, file=f)
    q = randint(int(1), int(1e6))
    print(q, file=f)
    for i in range(q):
        l = randint(1, n)
        r = randint(l, n)
        k = randint(0, m - 1)
        print(l, r, k, file=f)
    f.close()
    startTime = time.time()
    os.system("./../test < %d.in > %d.out" % (t, t))
    maxTime = max(maxTime, time.time() - startTime)
print(maxTime)