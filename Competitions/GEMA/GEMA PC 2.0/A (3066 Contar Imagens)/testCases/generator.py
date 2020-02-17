import os
from random import random, randint
os.system("g++ ./../A.cpp -o ./../test")

testCases = int(input())
for t in range(1, testCases + 1):
    f = open("%d.in" % t, "w")
    n, m, nn, mm = randint(1, 50), randint(1, 50), randint(1, 3), randint(1, 3)
    print(n, m, file=f)
    a1 = [[randint(0, 1) for j in range(m)] for i in range(n)]
    for line in a1:
        print(*line, file=f)
    print(nn, mm, file=f)
    a2 = [[randint(0, 1) for j in range(mm)] for i in range(nn)]
    for line in a2:
        print(*line, file=f)
    f.close()
    os.system("./../test < %d.in > %d.out" % (t, t))