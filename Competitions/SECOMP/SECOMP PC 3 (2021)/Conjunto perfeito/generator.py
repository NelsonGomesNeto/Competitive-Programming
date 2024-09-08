import os
import shutil
from random import random, randint
os.system("g++ code.cpp -o test -std=c++17")

shutil.rmtree("tests", ignore_errors=True)
os.mkdir("tests")

testCases = int(input())
for t in range(1, testCases + 1):
    f = open("tests/%d.in" % t, "w")

    tt = t - 1
    a = [(tt >> i) & 1 for i in range(3)]
    a = [2*randint(1, int(5e4) - 1) + aa for aa in a]
    print(*a, file=f)

    f.close()

    os.system("./test < tests/%d.in > tests/%d.out" % (t, t))
    # os.system("cat %d.in" % t)
    print(*a, end=' -> ')
    f = open("tests/%d.out" % t, "r")
    print(f.readline(), end="")
    f.close()
    # os.system("cat %d.out" % t)