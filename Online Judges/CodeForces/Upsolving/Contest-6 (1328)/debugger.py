import os
from random import randint
from filecmp import cmp

os.system("g++ D2.cpp -o test -std=c++17")

while True:
    f = open("big", "w")
    print(1, file=f)
    n = randint(3, 20)
    print(n, file=f)
    a = [randint(1, 5) for i in range(n)]
    print(*a, file=f)
    f.close()

    os.system("./test < big > my")
    if not cmp("my", "cor"):
        break
    print("Passou")