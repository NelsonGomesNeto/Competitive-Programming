import os
import shutil
from random import random, randint
os.system("g++ code.cpp -o test -std=c++17")

shutil.rmtree("tests", ignore_errors=True)
os.mkdir("tests")

testCases = int(input())
for t in range(1, testCases + 1):
    f = open("tests/%d.in" % t, "w")

    tt = randint(1, int(1e3))
    print(tt, file=f)

    max_x = 1 << 60

    for i in range(tt):
        a, b = [randint(0, max_x) for _ in range(2)]
        ab = a ^ b
        c = 0
        op = randint(0, 3)
        if op == 0: # and will be non zero
            for bit in range(0, 61):
                abi = (ab >> bit) & 1
                if abi == 1:
                    c |= 1 << bit
                else:
                    c |= randint(0, 1) << bit
        elif op == 1: # or will be non zero
            for bit in range(0, 61):
                abi = (ab >> bit) & 1
                if abi == 0:
                    c |= 0 << bit
                else:
                    c |= randint(0, 1) << bit
        elif op == 2:
            c = ab
        else: # anything
            c = randint(0, max_x)

        print(a, b, c, file=f)

    f.close()

    os.system("./test < tests/%d.in > tests/%d.out" % (t, t))
