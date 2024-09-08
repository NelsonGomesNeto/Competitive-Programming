import os
from random import randint
from filecmp import cmp

os.system("g++ 6035ColorfulTree.cpp -o test -std=c++17")


def root(u):
    if parent[u] < 0:
        return u
    parent[u] = root(parent[u])
    return parent[u]
def merge(u, v):
    u = root(u)
    v = root(v)
    if parent[u] > parent[v]:
        u, v = v, u
    parent[u] += parent[v]
    parent[v] = u

while True:
    f = open("big", "w")
    for t in range(100):
        n = randint(2, 1000)
        print(n, file=f)
        colors = [randint(1, n) for i in range(n)]
        print(*colors, file=f)
        parent = [-1] * (n + 1)
        for i in range(n - 1):
            u, v = randint(1, n), randint(1, n)
            while root(u) == root(v):
                u, v = randint(1, n), randint(1, n)
            print(u, v, file=f)
            merge(u, v)
    f.close()

    os.system("./test < big > my")
    f = open("my", "r")
    failed = False
    for line in f.readlines():
        if "NOT OK" in line:
            failed = True
    f.close()
    if failed:
        break
    # if not cmp("my", "cor"):
    #     break
    print("Passou")