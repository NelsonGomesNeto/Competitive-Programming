import os
from random import randint
from filecmp import cmp

os.system("g++ A.cpp -o test -std=c++17")
os.system("g++ bugA.cpp -o bug -std=c++17")

while True:
    f = open("big", "w")
    t = 1000
    print(t, file=f)
    n = randint(1, 1000)
    a = randint(1, 1000)
    b = randint(0, a - 1)
    d = randint(1, 1000)
    c = randint(0, d - 1)
    print(n, a, b, c, d, file=f)
    f.close()

    os.system("./test < big > my")
    os.system("./bug < big > cor")
    if not cmp("my", "cor"):
        break
    print("Passou")