import os
from random import randint, shuffle
from filecmp import cmp

os.system("g++ G.cpp -o test -std=c++17")
os.system("g++ Gnaive.cpp -o Gnaive -std=c++17")

while True:
    f = open("big", "w")
    n = randint(1, 10)
    m = randint(1, n)
    print(n, m, file=f)
    a = list(range(1, m + 1))
    while len(a) < n:
        a.append(randint(1, m))
    shuffle(a)
    print(*a, file=f)
    f.close()

    os.system("./test < big > my")
    os.system("./Gnaive < big > cor")
    if not cmp("my", "cor"):
        break
    print("Passou")