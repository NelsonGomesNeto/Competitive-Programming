import os
from random import randint, shuffle
from filecmp import cmp

os.system("g++ abc194F.cpp -o test -std=c++17")
os.system("g++ bug.cpp -o bug -std=c++17")

p = 0
while True:
    f = open("big", "w")

    sz = randint(1, 10)
    n = [hex(randint(i == 0, 15))[2].upper() for i in range(sz)]
    k = randint(1, 16)
    print("".join(n), k, file=f)

    f.close()

    os.system("./test < big > my")
    os.system("./bug < big > cor")
    if not cmp("my", "cor"):
        break
    p += 1
    print("Passou", p)