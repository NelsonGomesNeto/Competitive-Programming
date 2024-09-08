import os
import shutil
from random import random, randint
os.system("g++ code.cpp -o test -std=c++17")

shutil.rmtree("tests", ignore_errors=True)
os.mkdir("tests")

testCases = int(input())
for t in range(1, testCases + 1):
    f = open("tests/%d.in" % t, "w")

    a = [randint(0, int(1e9)) for _ in range(3)]
    print(*a, file=f)

    f.close()

    os.system("./test < tests/%d.in > tests/%d.out" % (t, t))
    # os.system("cat %d.in" % t)
    print(*a, a[-1] % 3, end=' -> ')
    f = open("tests/%d.out" % t, "r")
    print(f.readline(), end="")
    f.close()
    # os.system("cat %d.out" % t)