import os
from random import randint
from filecmp import cmp

os.system("g++ code.cpp -o test -std=c++17")
os.system("g++ naive.cpp -o bug -std=c++17")

while True:
    f = open("big", "w")

    n = 10
    print(n, file=f)
    a = set()
    while len(a) < n:
        a.add(randint(1, 40))
    a = list(a)
    print(*a, file=f)

    f.close()

    os.system("./test < big > my")
    os.system("./bug < big > cor")
    if not cmp("my", "cor"):
        break
    print("Passou")