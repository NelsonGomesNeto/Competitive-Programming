import os
from random import randint
from filecmp import cmp

os.system("g++ D.cpp -o test -std=c++17")
os.system("g++ 'D - bug.cpp' -o bug -std=c++17")

while True:
    f = open("big", "w")
    n = randint(5, 10)
    print(n, file=f)
    a = [randint(1, n) for i in range(n)]
    print(*a, file=f)
    f.close()

    os.system("./test < big > my")
    os.system("./bug < big > cor")
    if not cmp("my", "cor"):
        break
    print("Passou")