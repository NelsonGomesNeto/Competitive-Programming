import os
from random import randint, shuffle
from filecmp import cmp

os.system("g++ code.cpp -o code -std=c++17 -O2")
os.system("g++ naive.cpp -o naive -std=c++17 -O2")

while True:
    f = open("big", "w")

    test_cases = 2000
    print(test_cases, file=f)

    for _ in range(test_cases):
        n, k = randint(2, 5), randint(0, 10)
        print(n, k, file=f)

        a = list(range(1, n + 1))
        a = [randint(1, n) for _ in range(n)]
        shuffle(a)
        print(*a, file=f)

        b = a
        shuffle(b)
        print(*b, file=f)

    f.close()

    os.system("./code < big > my")
    os.system("./naive < big > cor")
    if not cmp("my", "cor"):
        break
    print("Passou")