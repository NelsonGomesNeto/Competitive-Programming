import os
from random import randint
from filecmp import cmp

os.system("g++ E.cpp -o test -std=c++17")
os.system("g++ bug.cpp -o bug -std=c++17")

while True:
    f = open("big", "w")

    n, q = randint(3, 10), 10
    print(n, q, file=f)
    a = [randint(1, 10) for _ in range(n)]
    print(*a, file=f)
    for _ in range(q):
        op = randint(1, 2)
        x, y = 0, 0
        if op == 1:
            x, y = randint(1, n), randint(1, 10)
        else:
            x = randint(1, n - 1)
            y = randint(x + 1, n)
        print(op, x, y, file=f)

    f.close()

    os.system("./test < big > my")
    os.system("./bug < big > cor")
    if not cmp("my", "cor"):
        break
    print("Passou")