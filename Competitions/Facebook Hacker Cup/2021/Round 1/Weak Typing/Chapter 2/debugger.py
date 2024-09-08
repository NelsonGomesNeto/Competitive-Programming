import os
from random import randint
from filecmp import cmp

os.system("g++ code.cpp -o test -std=c++17 -O2")
os.system("g++ naive.cpp -o naive -std=c++17 -O2")

while True:
    f = open("big", "w")
    t = 1
    max_n = 10000
    print(t, file=f)
    for _ in range(t):
        n = randint(1, max_n)
        print(n, file=f)
        s = ''.join(["XFO"[randint(0, 2)] for _ in range(n)])
        print(s, file=f)
    f.close()

    os.system("./test < big > my")
    os.system("./naive < big > cor")
    if not cmp("my", "cor"):
        break
    print("Passou")
