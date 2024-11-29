import os
from random import randint
from filecmp import cmp

os.system("g++ G.cpp -o p -std=c++23 -O2")
os.system("g++ Gnaive.cpp -o naive -std=c++23 -O2")

while True:
    with open("debug_in", "w") as f:
        test_cases = 1000
        print(test_cases, file=f)
        for _ in range(test_cases):
            n = randint(1, 10)
            print(n, file=f)
            p = [randint(0, i) for i in range(n)]
            print(*p, file=f)
            a = [randint(1, 50) for _ in range(n)]
            print(*a, file=f)

    os.system("./p < debug_in > my")
    os.system("./naive < debug_in > cor")
    if not cmp("my", "cor"):
        break
    print("Passou")
