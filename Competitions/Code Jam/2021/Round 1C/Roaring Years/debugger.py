import os
from random import randint
from filecmp import cmp

os.system("g++ \"code - smart.cpp\" -o test -std=c++17 -O2")
os.system("g++ bug.cpp -o bug -std=c++17 -O2")

now = 0
while True:
    f = open("big", "w")
    t = 100
    print(t, file=f)
    for _ in range(t):
        print(randint(1, int(1e6)), file=f)
    f.close()

    os.system("./test < big > my")
    os.system("./bug < big > cor")
    if not cmp("my", "cor"):
        break
    print("Passou", now)
    now += 1