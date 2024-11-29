import os
from random import randint
from filecmp import cmp

os.system("g++ E.cpp -o p -std=c++23 -O2")
os.system("g++ Enaive.cpp -o naive -std=c++23 -O2")

while True:
    with open("debug_in", "w") as f:
        n = randint(1, 10)
        q = randint(1, 100000)
        print(n, q, file=f)
        s = ["12/"[randint(0, 2)] for _ in range(n)]
        print("".join(s), file=f)
        for _ in range(q):
            lo = randint(1, n)
            hi = randint(lo, n)
            print(lo, hi, file=f)

    os.system("./p < debug_in > my")
    os.system("./naive < debug_in > cor")
    if not cmp("my", "cor"):
        break
    print("Passou")
