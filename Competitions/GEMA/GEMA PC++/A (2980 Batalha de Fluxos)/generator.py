import os
from random import random, randint, shuffle
os.system("g++ 2980BatalhaDeFluxos.cpp -o ./test")

testCases = int(input())
for t in range(1, testCases + 1):
    f = open("%d.in" % t, "w")
    n = randint(100, 100)
    print(n, file=f)
    for p in range(2):
        for i in range(n):
            health, power, k = 1000, 1, randint(n, n)
            permutation = list(range(n))
            shuffle(permutation)
            reachable = []
            for r in range(k):
                reachable += [permutation[r]]
            print(health, power, k, *reachable, file=f)
    f.close()
    os.system("time ./test < %d.in > %d.out" % (t, t))