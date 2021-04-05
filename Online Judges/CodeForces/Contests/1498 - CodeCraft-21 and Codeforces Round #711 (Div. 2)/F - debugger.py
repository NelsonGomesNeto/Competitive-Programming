import os
from random import randint
from filecmp import cmp

os.system("g++ 'F - Christmas Game.cpp' -o test -std=c++17")
os.system("g++ bug.cpp -o bug -std=c++17")

def root(u):
    if parents[u] < 0: return u
    parents[u] = root(parents[u])
    return parents[u]

def merge(u, v):
    u, v = root(u), root(v)
    if u == v: return
    if parents[u] > parents[v]:
        u, v = v, u
    parents[u] += parents[v]
    parents[v] = u

while True:
    f = open("big", "w")
    n = randint(4, 4)
    k = randint(1, 6)
    print(n, k, file=f)

    parents = [-1] * (n + 1)
    for _ in range(n - 1):
        u, v = randint(1, n), randint(1, n)
        while root(u) == root(v):
            u, v = randint(1, n), randint(1, n)
        print(u, v, file=f)
        merge(u, v)

    a = [randint(1, 100) for _ in range(n)]
    print(*a, file=f)
    f.close()

    os.system("./test < big > my")
    os.system("./bug < big > cor")
    if not cmp("my", "cor"):
        break
    print("Passou")