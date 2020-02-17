import os
import time
from random import random, randint
os.system("g++ ./../E.cpp -o ./../test")

testCases = int(input())
maxTime = 0
for t in range(1, testCases + 1):
    f = open("%d.in" % t, "w")
    n = randint(int(1), int(1e5))
    print(n, file=f)
    a = [randint(0, int(1e9)) for i in range(n)]
    aSum = sum(a)
    print(*a, file=f)
    q = randint(int(1), int(1e5))
    print(q, file=f)
    for i in range(q):
        l, x = randint(1, n), randint(0, aSum + 1)
        print(l, x, file=f)
    f.close()
    startTime = time.time()
    os.system("./../test < %d.in > %d.out" % (t, t))
    maxTime = max(maxTime, time.time() - startTime)
print(maxTime)