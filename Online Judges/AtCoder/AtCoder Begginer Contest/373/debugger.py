import os
from random import randint
from filecmp import cmp

os.system("g++ E.cpp -o p -std=c++23")
os.system("g++ Enaive.cpp -o naive -std=c++23")

while True:
    f = open("big", "w")
    n = randint(1, 5)
    m = randint(1, n)
    k = randint(1, 10)
    a = [randint(0, 10) for _ in range(n)]
    print(n, m, k, file=f)
    print(*a, file=f)
    f.close()

    os.system("./p < big > my")
    os.system("./naive < big > cor")
    if not cmp("my", "cor"):
        break
    print("Passou")