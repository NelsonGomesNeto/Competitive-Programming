import os
from random import randint, shuffle
from filecmp import cmp

os.system("g++ F.cpp -o p -std=c++23 -O2")
os.system("g++ Fnaive.cpp -o naive -std=c++23 -O2")

while True:
    with open("debug_in", "w") as f:
        test_cases = 1000
        for _ in range(test_cases):
            n = randint(1, 16)
            print(n, file=f)
            a = []
            for i in range(n):
                for _ in range(4):
                    a.append(i % 5 + 1)
            shuffle(a)
            a = a[:n]
            print(*a, file=f)

    os.system("./p < debug_in > my")
    os.system("./naive < debug_in > cor")
    if not cmp("my", "cor"):
        break
    print("Passou")
