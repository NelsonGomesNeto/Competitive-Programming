import os
from random import randint
from filecmp import cmp

os.system("g++ F.cpp -o p -std=c++23")
os.system("g++ naiveF.cpp -o naive -std=c++23")

while True:
    f = open("big", "w")
    n, q = randint(1, 5), randint(1, 5)
    print(n, q, file=f)
    for _ in range(q):
        a, b, d = randint(1, n), randint(1, n), randint(-10, 10)
        print(a, b, d, file=f)
    f.close()

    os.system("./p < big > my")
    os.system("./naive < big > cor")
    if not cmp("my", "cor"):
        break
    print("Passou")