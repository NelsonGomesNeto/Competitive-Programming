import os
from random import random, randint
os.system("g++ 2976EntidadeEasPedrasDeGranizo.cpp -o ./test")

testCases = int(input())
for t in range(1, testCases + 1):
    f = open("%d.in" % t, "w")
    n = randint(1, (1 << 32) - 1)
    print(n, file=f)
    f.close()
    os.system("./test < %d.in > %d.out" % (t, t))