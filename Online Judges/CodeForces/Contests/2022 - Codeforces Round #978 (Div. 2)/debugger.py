import os
from random import randint
from filecmp import cmp

os.system("g++ B.cpp -o p -std=c++23 -O2")
os.system("g++ BNaive.cpp -o naive -std=c++23 -O2")

while True:
    f = open("big", "w")
    test_cases = int(10)
    print(test_cases, file=f)
    for _ in range(test_cases):
        n = randint(2, 4)
        x = randint(1, 4)
        print(n, x, file=f)
        a = [randint(1, 3) for _ in range(n)]
        print(*a, file=f)
    f.close()

    os.system("./p < big > my")
    os.system("./naive < big > cor")
    if not cmp("my", "cor"):
        break
    print("Passou")