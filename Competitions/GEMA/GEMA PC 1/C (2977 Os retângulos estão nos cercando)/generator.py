import os
from random import random, randint
os.system("g++ 2977OsRetângulosEstãoNosCercando.cpp -o ./test")

testCases = int(input())
for t in range(1, testCases + 1):
    f = open("%d.in" % t, "w")
    k = randint(1, 10)
    for j in range(k):
        n = randint(1, 50)
        print(n, file=f)
        for p in range(n):
            a, b = randint(0, 499), randint(0, 499)
            c, d = randint(a + 1, 500), randint(b + 1, 500)
            print(a, b, c, d, file=f)
    print(0, file=f)
    f.close()
    os.system("./test < %d.in > %d.out" % (t, t))