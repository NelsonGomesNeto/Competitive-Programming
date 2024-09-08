import os
from random import randint
from filecmp import cmp

os.system("g++ code.cpp -o test -std=c++17")
os.system("g++ naive.cpp -o bug -std=c++17")

while True:
    f = open("big", "w")

    test_cases = 100

    for _ in range(test_cases):
        n, q = randint(200, 200), 1
        print(n, q, file=f)
        a = [randint(1, int(5)) for _ in range(n)]
        print(*a, file=f)
        for _ in range(q):
            l = randint(1, n)
            r = randint(l, n)
            d = randint(0, int(100))
            print(l, r, q, file=f)
        print(file=f)

    f.close()

    os.system("./test < big > my")
    os.system("./bug < big > cor")
    if not cmp("my", "cor"):
        break
    print("Passou")