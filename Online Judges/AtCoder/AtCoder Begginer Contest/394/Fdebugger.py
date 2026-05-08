import os
from random import randint
from filecmp import cmp

os.system("g++-14 F.cpp -o p -std=c++20 -O2")
os.system("g++-14 Fnaive.cpp -o naive -std=c++20 -O2")

while True:
    with open("debug_in", "w") as f:
        n = randint(6, 10)
        print(n, file=f)
        for i in range(2, n + 1):
            u = i
            v = randint(1, i - 1)
            print(u, v, file=f)

    os.system("./p < debug_in > my")
    os.system("./naive < debug_in > cor")
    if not cmp("my", "cor"):
        break
    print("Passou")
