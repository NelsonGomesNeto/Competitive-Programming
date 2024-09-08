import os
from random import randint
from filecmp import cmp

os.system("g++ D.cpp -o test -std=c++17")
os.system("g++ bug.cpp -o bug -std=c++17")

while True:
    f = open("big", "w")
    n, q = 5, 5
    print(n, q, file=f)
    a = [randint(1, 10) for i in range(n)]
    print(*a, file=f)
    for qq in range(q):
        i, x = randint(1, n), randint(1, 10)
        print(i, x, file=f)
    f.close()

    os.system("./test < big > my")
    os.system("./bug < big > cor")
    if not cmp("my", "cor"):
        break
    print("Passou")