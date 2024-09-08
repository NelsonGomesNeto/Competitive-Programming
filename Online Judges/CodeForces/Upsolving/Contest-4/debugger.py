import os
from random import randint
from filecmp import cmp

os.system("g++ D.cpp -o test -std=c++17")
os.system("g++ D1.cpp -o bug -std=c++17")

while True:
    f = open("big", "w")
    print(10, file=f)
    for i in range(10):
        lol = ""
        for i in range(10):
            lol += chr(randint(ord('a'), ord('c')))
        print(lol, file=f)
    f.close()

    os.system("./test < big > my")
    os.system("./bug < big > cor")
    if not cmp("my", "cor"):
        break
    print("Passou")