import os
from random import randint
from filecmp import cmp

os.system("g++-14 F.cpp -o p -std=c++20 -O2")
os.system("g++-14 Fnaive.cpp -o naive -std=c++20 -O2")

while True:
    with open("debug_in", "w") as f:
        n = randint(1, 5)
        print(n, file=f)
        a = [randint(1, i) for i in range(1, n + 1)]
        print(*a, file=f)

    os.system("./p < debug_in > my")
    os.system("./naive < debug_in > cor")
    if not cmp("my", "cor"):
        break
    print("Passou")
