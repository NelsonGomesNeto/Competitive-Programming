import os
import time
from random import random, randint
os.system("g++ ./../C.cpp -o ./../test")

maxTime = 0
testCases = int(input())
for t in range(1, testCases + 1):
    f = open("%d.in" % t, "w")
    n, m = randint(1, 1000), randint(1, 1000)
    print(n, m, file=f)
    for i in range(n):
        for j in range(m):
            print(randint(0, 9), end='', file=f)
        print(file=f)
    f.close()
    startTime = time.time()
    os.system("./../test < %d.in > %d.out" % (t, t))
    maxTime = max(maxTime, time.time() - startTime)
print(maxTime)