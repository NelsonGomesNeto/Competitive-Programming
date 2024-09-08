import os
from random import randint
from filecmp import cmp

os.system("g++ F.cpp -o test -std=c++23")
os.system("g++ naiveF.cpp -o bug -std=c++23")

while True:
    f = open("big", "w")
    test_cases = 1
    for _ in range(test_cases):
        n = randint(1, 5)
        q = randint(1, 5)
        print(n, q, file=f)

        s = "".join(["01"[randint(0, 1)] for i in range(n)])
        print(s, file=f)

        for i in range(q):
            op = randint(1, 2)
            lo = randint(1, n)
            hi = randint(lo, n)
            print(op, lo, hi, file=f)

        print(file=f)
    f.close()

    os.system("./test < big > my")
    os.system("./bug < big > cor")
    if not cmp("my", "cor"):
        break
    print("Passou")