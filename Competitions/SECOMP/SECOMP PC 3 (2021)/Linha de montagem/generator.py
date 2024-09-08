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
    max_x = int(1e5)

    n_sum = 0
    for j in range(tt):
        n = randint(2, max_n - n_sum - 2*(tt - j - 1)) if t != testCases else max_n
        n_sum += n
        print(n, file=f)
        e = [randint(0, max_x) for _ in range(2)]
        print(*e, file=f)
        for i in range(2):
            a = [randint(0, max_x) for _ in range(n)]
            print(*a, file=f)
        for i in range(2):
            ts = [randint(0, max_x) for _ in range(n - 1)]
            print(*ts, file=f)
        x = [randint(0, max_x) for _ in range(2)]
        print(*x, file=f)

    assert(n_sum <= max_n)

    f.close()

    os.system("./test < tests/%d.in > tests/%d.out" % (t, t))
