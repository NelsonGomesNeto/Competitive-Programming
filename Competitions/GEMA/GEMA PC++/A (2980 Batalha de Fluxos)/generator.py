import os
import filecmp
from random import random, randint, shuffle
os.system("g++ 2980BatalhaDeFluxos.cpp -o ./test")
os.system("g++ naive.cpp -o ./naive")

testCases = int(input())
t = 1
while t <= testCases:
    f = open("%d.in" % t, "w")
    n = randint(1, 100)
    print(n, file=f)
    for p in range(2):
        for i in range(n):
            health, power, k = randint(1000, 1000), randint(1, 1000), randint(1, n)
            permutation = list(range(n))
            shuffle(permutation)
            reachable = []
            for r in range(k):
                reachable += [permutation[r]]
            print(health, power, k, *reachable, file=f)
    f.close()
    os.system("./test < %d.in > %d.out" % (t, t))
    os.system("./naive < %d.in > naiveOut" % t)
    if not filecmp.cmp("naiveOut", "%d.out" % t):
        t += 1
        print("FOI", t)