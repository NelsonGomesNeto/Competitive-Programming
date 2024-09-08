import os
from random import randint
from filecmp import cmp

os.system("g++ code.cpp -o test -std=c++17 -O2")
os.system("g++ bug.cpp -o bug -std=c++17 -O2")

while True:
    f = open("big", "w")
    t = 1000
    for _ in range(t):
        n = 100
        print(n, file=f)
        for _ in range(n):
            x, y = randint(-int(1e9), int(1e9)), randint(-int(1e9), int(1e9))
            a, s = randint(0, int(1e9)), randint(0, int(1e9))
            print(x, y, a, s, file=f)
    f.close()

    os.system("./test < big > my")
    os.system("./bug < big > cor")
    if not cmp("my", "cor"):
        break
    print("Passou")