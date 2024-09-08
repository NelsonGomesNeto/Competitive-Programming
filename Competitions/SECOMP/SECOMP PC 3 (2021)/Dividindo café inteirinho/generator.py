import os
import shutil
from random import random, randint
os.system("g++ code.cpp -o test -std=c++17")

shutil.rmtree("tests", ignore_errors=True)
os.mkdir("tests")

testCases = int(input())
for t in range(1, testCases + 1):
    f = open("tests/%d.in" % t, "w")

    tt = randint(1, int(1e3)) if t != testCases else 1
    print(tt, file=f)

    max_n = int(1e5)
    max_x = int(1e13)

    n_sum = 0
    for j in range(tt):
        n = randint(1, max_n - n_sum - (tt - j - 1)) if t != testCases else max_n
        n_sum += n
        L = randint(1, max_x)
        print(n, L, file=f)
        for i in range(n):
            a = randint(1, int(1e5))
            b = randint(1, int(1e10) // a)
            c = randint(1, max_x // a // b)
            print(a, b, c, file=f)

    assert(n_sum <= max_n)

    f.close()

    os.system("./test < tests/%d.in > tests/%d.out" % (t, t))
