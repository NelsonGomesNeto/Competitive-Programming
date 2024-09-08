import os
from random import randint
from filecmp import cmp

os.system("g++ C.cpp -o test -std=c++17")

while True:
    f = open("big", "w")
    for i in range(100):
        n = randint(2, 1000)
        print(n, file=f)
        a = [randint(100000, 200000) for i in range(n)]
        print(*a, file=f)
    f.close()

    os.system("./test < big > my")
    f = open("my", "r")
    failed = False
    for line in f.readlines():
        if "NOT OK" in line:
            failed = True
            break
    f.close()
    if failed:
        break
    print("Passou")