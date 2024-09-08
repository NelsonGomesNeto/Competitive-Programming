import os
from random import randint
from filecmp import cmp

os.system("g++ E.cpp -o p -std=c++23")
os.system("g++ naiveE.cpp -o naive -std=c++23")

def gen_string(size: int):
    return ''.join([chr(randint(ord('A'), ord('C'))) for _ in range(size)])

while True:
    f = open("big", "w")
    n = randint(1, 5)
    m = randint(1, min(n, 5))
    print(n, m, file=f)
    s = gen_string(n)
    print(s, file=f)
    t = gen_string(m)
    print(t, file=f)
    f.close()

    os.system("./p < big > my")
    os.system("./naive < big > cor")
    if not cmp("my", "cor"):
        break
    print("Passou")