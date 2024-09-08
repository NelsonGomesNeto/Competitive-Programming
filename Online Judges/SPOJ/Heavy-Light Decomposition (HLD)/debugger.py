import os
from random import randint
from filecmp import cmp

os.system("g++ QTREE6QueryOnATreeVI.cpp -o test -std=c++17")
os.system("g++ bug.cpp -o bug -std=c++17")


def root(u):
    if parents[u] < 0:
        return u
    parents[u] = root(parents[u])
    return parents[u]


def merge(u, v):
    u, v = root(u), root(v)
    if u == v: return
    if parents[u] > parents[v]: u, v = v, u
    parents[u] += parents[v]
    parents[v] = u


while True:
    f = open("big", "w")

    n, q = 6, 6
    parents = [-1]*(n + 1)

    print(n, file=f)
    for i in range(n - 1):
        u = randint(1, n - 1)
        v = randint(u + 1, n)
        while root(u) == root(v):
            u = randint(1, n - 1)
            v = randint(u + 1, n)
        merge(u, v)
        print(u, v, file=f)

    print(q, file=f)
    for i in range(q):
        op, u = randint(0, 1), randint(1, n)
        print(op, u, file=f)
    f.close()

    os.system("./test < big > my")
    os.system("./bug < big > cor")
    if not cmp("my", "cor"):
        break
    print("Passou")