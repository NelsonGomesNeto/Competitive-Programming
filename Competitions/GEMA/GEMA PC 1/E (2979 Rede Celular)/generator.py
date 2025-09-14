import os
from random import random, randint
os.system("g++ 2979RedeCelular.cpp -o ./test")

testCases = int(input())
for t in range(1, testCases + 1):
    f = open("%d.in" % t, "w")
    n, m = randint(1, int(1e5)), randint(1, int(1e5))
    print(n, m, file=f)
    a = [randint(-int(1e9), int(1e9)) for i in range(n)]
    a.sort()
    print(*a, file=f)
    b = [randint(-int(1e9), int(1e9)) for i in range(m)]
    b.sort()
    print(*b, file=f)
    f.close()
    os.system("./test < %d.in > %d.out" % (t, t))