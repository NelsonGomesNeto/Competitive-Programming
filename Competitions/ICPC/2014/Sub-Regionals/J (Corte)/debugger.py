import os
from random import random, randint
from math import pi, sin, cos
from filecmp import cmp

os.system("g++ J.cpp -o test -std=c++17")
os.system("g++ bug.cpp -o bug -std=c++17")

while True:
    f = open("big", "w")
    n = 7
    print(n, file=f)
    angles = []
    for i in range(2*n):
        angles += [random()*2*pi]
    angles.sort()
    for angle in angles:
        x, y = cos(angle), sin(angle)
        print(x, y, file=f)
    f.close()

    os.system("./test < big > my")
    os.system("./bug < big > cor")
    if not cmp("my", "cor"):
        break
    print("Passou")