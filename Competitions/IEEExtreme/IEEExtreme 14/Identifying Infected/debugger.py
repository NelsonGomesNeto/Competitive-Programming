import os
from random import randint
from filecmp import cmp

os.system("g++ bug.cpp -o test -std=c++17")
os.system("g++ bug2.cpp -o bug -std=c++17")

parent = []
def root(u):
    if parent[u] < 0:
        return u
    parent[u] = root(parent[u])
    return parent[u]
def merge(u, v):
    u, v = root(u), root(v)
    if u == v:
        return
    if parent[u] > parent[v]:
        u, v = v, u
    parent[u] += parent[v]
    parent[v] = u

while True:
    f = open("big", "w")
    n = 6
    parent = [-1] * (n + 1)
    m = randint(1, n * (n - 1) // 2)
    print(n, m, file=f)
    
    edges = []
    while len(edges) < m:
        u = randint(1, n - 1)
        v = randint(u + 1, n)
        while [u, v] in edges or [v, u] in edges:
            u = randint(1, n - 1)
            v = randint(u + 1, n)
        edges += [[u, v]]
        merge(u, v)
    for edge in edges:
        print(*edge, file=f)
    
    q = 10
    print(q, file=f)
    for i in range(q):
        u = randint(1, n - 1)
        v = randint(u + 1, n)
        while root(u) != root(v):
            u = randint(1, n - 1)
            v = randint(u + 1, n)
        print(u, v, file=f)

    f.close()

    os.system("./test < big > my")
    os.system("./bug < big > cor")
    if not cmp("my", "cor"):
        break
    print("Passou")