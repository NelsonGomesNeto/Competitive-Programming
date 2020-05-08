import os
from random import randint
from filecmp import cmp

os.system("g++ code.cpp -o test -std=c++17")
os.system("g++ bug.cpp -o bug -std=c++17")

p = 1
while True:
    f = open("big", "w")
    t = 100
    print(t, file=f)
    for i in range(t):
        n = int(1e4) if i <= 40 else int(1e3)
        d = randint(50, 50)
        a = [randint(1, int(360e9) - 1) for i in range(n)]
        # n = randint(1, 10)
        # d = randint(2, 6)
        # a = [randint(1, 20) if randint(0, 1) else randint(int(360e9) - 20, int(360e9) - 1) for i in range(n)]
        print(n, d, file=f)
        print(*a, file=f)
    f.close()

    break

    os.system("./test < big > my")
    os.system("./bug < big > cor")
    if not cmp("my", "cor"):
        break
    print("Passou", p)
    p += 1