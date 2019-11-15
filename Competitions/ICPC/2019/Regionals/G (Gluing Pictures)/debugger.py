import os
from random import randint
from filecmp import cmp

os.system("g++ G.cpp -o test -std=c++17")
os.system("g++ bug.cpp -o bug -std=c++17") # teu código aqui

while True:
    f = open("big", "w")
    n = randint(1, 40)
    s = ""
    for i in range(n):
        s += chr(randint(ord('A'), ord('Z')))
    print(s, file=f)
    q = 10
    print(q, file=f)
    for i in range(q):
        m = randint(1, 40)
        t = ""
        for i in range(m):
            t += chr(randint(ord('A'), ord('Z')))
        print(t, file=f)
    f.close()

    os.system("./test < big > cor")
    os.system("./bug < big > my")
    if not cmp("my", "cor"):
        break
    print("Passou")