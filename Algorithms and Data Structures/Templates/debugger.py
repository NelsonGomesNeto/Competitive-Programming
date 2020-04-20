import os
from random import randint
from filecmp import cmp

os.system("g++ .cpp -o test -std=c++17")
os.system("g++ bug.cpp -o bug -std=c++17")

while True:
    f = open("big", "w")

    f.close()

    os.system("./test < big > my")
    os.system("./bug < big > cor")
    if not cmp("my", "cor"):
        break
    print("Passou")