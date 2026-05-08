import os
from random import randint
from filecmp import cmp

os.system("g++-14 F.cpp -o p -std=c++20 -O2")
os.system("g++-14 Fayallaa.cpp -o naive -std=c++20 -O2")

MAX_X = int(3e1)

while True:
    with open("debug_in", "w") as f:
        test_cases = 10000
        for test_case in range(test_cases):
            n = randint(6, 7)
            print(n, file=f)
            c = [randint(1, 6) for _ in range(n)]
            print(*c, file=f)
            x = [randint(1, MAX_X) for _ in range(n)]
            print(*x, file=f)

    os.system("./p < debug_in > my")
    os.system("./naive < debug_in > cor")
    if not cmp("my", "cor"):
        break
    print("Passou")
