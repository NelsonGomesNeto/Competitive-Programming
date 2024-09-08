import os
from random import randint
from filecmp import cmp

os.system("g++ code.cpp -o code -std=c++17 -O2")
os.system("g++ naive.cpp -o naive -std=c++17 -O2")

while True:
    f = open("big", "w")

    test_cases = 1000
    print(test_cases, file=f)
    for _ in range(test_cases):
        # n = int(1e6)
        n = randint(2, 10)
        k = randint(0, int(1e9))
        d = randint(0, int(1e9))
        print(n, k, d, file=f)
        print(0, 0, file=f)
        has = set()
        for _ in range(n - 2):
            x, y = randint(1, int(1e6) - 1), randint(1, int(1e6) - 1)
            while (x, y) in has:
                x, y = randint(1, int(1e6) - 1), randint(1, int(1e6) - 1)
            has.add((x, y))
            print(x, y, file=f)
        print(int(1e6), int(1e6), file=f)

    f.close()

    os.system("./code < big > my")
    os.system("./naive < big > cor")
    if not cmp("my", "cor"):
        break
    print("Passou")