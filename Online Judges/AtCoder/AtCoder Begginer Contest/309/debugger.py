import os
from random import randint
from filecmp import cmp

os.system("g++ F.cpp -o p -std=c++17")
os.system("g++ naiveF.cpp -o np -std=c++17")

MAX_V = 6

def a():
    return randint(1, MAX_V)

while True:
    f = open("big", "w")
    tests = 1
    for _ in range(tests):
        n = randint(2, 5)
        print(n, file=f)
        for _ in range(n):
            print(a(), a(), a(), file=f)
    f.close()

    os.system("./p < big > my")
    os.system("./np < big > cor")
    if not cmp("my", "cor"):
        break
    print("Passou")