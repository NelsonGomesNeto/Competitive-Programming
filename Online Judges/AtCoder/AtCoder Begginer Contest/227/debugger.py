import os
from random import randint
from filecmp import cmp

os.system("g++ D.cpp -o test -std=c++17")
os.system("g++ naiveD.cpp -o bug -std=c++17")

while True:
    f = open("big", "w")
    t = 1
    for _ in range(t):
        n = randint(2, 6)
        k = randint(2, n)
        print(n, k, file=f)
        a = [randint(1, int(20)) for _ in range(n)]
        print(*a, file=f)
    f.close()

    os.system("./test < big > my")
    os.system("./bug < big > cor")
    if not cmp("my", "cor"):
        break
    print("Passou")