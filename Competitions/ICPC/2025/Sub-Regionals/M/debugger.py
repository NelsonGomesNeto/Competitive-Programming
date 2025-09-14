import os
from random import randint
from filecmp import cmp

os.system("g++ code.cpp -o p -std=c++23 -O2")
os.system("g++ naive.cpp -o naive -std=c++23 -O2")

total_cases = 0
while True:
    with open("debug_in", "w") as f:
        test_cases = int(1000)
        for _ in range(test_cases):
            n = randint(1, int(1e3))
            k = randint(1, n)
            print(n, k, file=f)
            a = [randint(1, int(1e3)) for _ in range(n)]
            print(*a, file=f)
        total_cases += test_cases

    os.system("./p < debug_in > my")
    os.system("./naive < debug_in > cor")
    if not cmp("my", "cor"):
        break
    print("Passou", total_cases, "(%.2e)" % (total_cases))
