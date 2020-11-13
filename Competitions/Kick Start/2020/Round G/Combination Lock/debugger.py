import os
from random import randint
from filecmp import cmp

os.system("g++ code.cpp -o test -std=c++17")
os.system("g++ bug.cpp -o bug -std=c++17")

while True:
    f = open("big", "w")
    tests = 10
    print(tests, file=f)
    for _ in range(tests):
        w = randint(2, 6)
        n = randint(2, 10)
        x = [randint(1, n) for i in range(w)]
        print(w, n, file=f)
        print(*x, file=f)
    f.close()

    os.system("./test < big > my")
    os.system("./bug < big > cor")
    if not cmp("my", "cor"):
        break
    print("Passou")