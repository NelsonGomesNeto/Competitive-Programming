import os
from random import randint
from filecmp import cmp

os.system("g++ code.cpp -o code -std=c++17 -O2")

while True:
    f = open("big", "w")
    test_cases = 50000
    print(test_cases, file=f)
    for test_case in range(test_cases):
        n = int(10)
        print(n, file=f)
        for _ in range(n):
            x, y = randint(0, int(1e9)), randint(0, int(1e9))
            print(x, y, file=f)
        q = int(10)
        print(q, file=f)
        for _ in range(q):
            x, y = randint(0, int(1e9)), randint(0, int(1e9))
            print(x, y, file=f)
    f.close()

    os.system("./code < big > my")
    f = open("my", "r")
    fuck = False
    lines = f.readlines()
    f.close()
    for line in lines:
        if "-" in line:
            fuck = True
            break
    if fuck:
        break
    print("Passou")