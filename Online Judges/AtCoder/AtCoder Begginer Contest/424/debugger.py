import os
from random import randint
from filecmp import cmp

os.system("g++ D.cpp -o p -std=c++23 -O2")
os.system("g++ Dnaive.cpp -o naive -std=c++23 -O2")

total_cases = 0
while True:
    with open("debug_in", "w") as f:
        test_cases = int(1e2)
        print(test_cases, file=f)
        for _ in range(test_cases):
            n = randint(2, 5)
            m = randint(2, 5)
            print(n, m, file=f)
            for _ in range(n):
                line = ''.join([".#######"[randint(0, 7)] for _ in range(m)])
                print(line, file=f)
            pass
        total_cases += test_cases

    os.system("./p < debug_in > my")
    os.system("./naive < debug_in > cor")
    if not cmp("my", "cor"):
        break
    print("Passou", total_cases, "(%.2e)" % (total_cases))
