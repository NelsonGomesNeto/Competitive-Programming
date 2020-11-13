import os
from random import randint
from filecmp import cmp

os.system("g++ Rooks.cpp -o test -std=c++17")

def conflict(newPos, a):
    for i in range(len(a)):
        if newPos[0] == a[i][0] or newPos[1] == a[i][1]:
            return True
    return False

def genPos():
    a = []
    for i in range(n):
        newPos = [randint(80, 99), randint(80, 99)]
        while conflict(newPos, a):
            newPos = [randint(80, 99), randint(80, 99)]
        a += [newPos]
    return a

while True:
    f = open("big", "w")
    n = 5
    print(n, file=f)
    now, dest = genPos(), genPos()
    for i in range(n):
        print(*now[i], file=f)
    for i in range(n):
        print(*dest[i], file=f)
    f.close()

    os.system("./test < big > out")
    os.system("python3 tester.py > out2")
    if not cmp("out2", "cor"):
        break
    print("Passou")