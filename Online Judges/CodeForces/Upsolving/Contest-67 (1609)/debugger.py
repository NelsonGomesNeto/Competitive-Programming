import os
from random import randint
from filecmp import cmp

os.system("g++ E.cpp -o test -std=c++17")
os.system("g++ naiveE.cpp -o bug -std=c++17")

while True:
    f = open("big", "w")
    n = randint(6, 15)
    q = 10
    s = ''.join(["abc"[randint(0, 2)] for _ in range(n)])
    print(n, q, file=f)
    print(s, file=f)
    for i in range(q):
        p = randint(1, n)
        c = "abc"[randint(0, 2)]
        print(p, c, file=f)
    f.close()

    os.system("./test < big > my")
    os.system("./bug < big > cor")
    if not cmp("my", "cor"):
        break
    print("Passou")