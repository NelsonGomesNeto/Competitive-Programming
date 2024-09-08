import os
from random import randint
from filecmp import cmp

os.system("g++ code.cpp -o test -std=c++17")
os.system("g++ naive.cpp -o naive -std=c++17")

while True:
    f = open("big", "w")

    t = 10
    for _ in range(t):
        n = 5
        print(n, file=f)
        a = [randint(1, 10) for _ in range(n)]
        print(*a, file=f)

    f.close()

    os.system("./test < big > my")
    os.system("./naive < big > cor")
    if not cmp("my", "cor"):
        break
    print("Passou")