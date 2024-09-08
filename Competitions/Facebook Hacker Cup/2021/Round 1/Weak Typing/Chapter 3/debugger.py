import os
from random import randint
from filecmp import cmp

os.system("g++ code.cpp -o test -std=c++17")
os.system("g++ naive.cpp -o bug -std=c++17")

while True:
    f = open("big", "w")
    t = 100
    max_n = int(8e5)
    print(t, file=f)
    for _ in range(t):
        n = randint(1, max_n)

        s, sz = '', 0
        while sz < n:
            c = "XFO."[randint(0, 3)]
            if c == '.': sz *= 2
            else: sz += 1
            s += c

        n = len(s)
        print(n, file=f)
        print(s, file=f)
    f.close()

    os.system("./test < big > my")
    os.system("./bug < big > cor")
    if not cmp("my", "cor"):
        break
    print("Passou")