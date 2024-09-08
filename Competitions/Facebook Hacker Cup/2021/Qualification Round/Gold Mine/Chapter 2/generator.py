import os
from random import random, randint

p = []
def init_dsu(n: int):
    p.clear()
    for _ in range(n):
        p.append(-1)
def root(u: int):
    if p[u] < 0: return u
    p[u] = root(p[u])
    return p[u]
def merge(u: int, v: int):
    u, v = root(u), root(v)
    if u == v: return
    if p[u] > p[v]: u, v = v, u
    p[u] += p[v]
    p[v] = u

f = open("big", "w")

test_cases = 30
print(test_cases, file=f)

for _ in range(1, test_cases + 1):
    n, k = 50, 50
    c = [randint(1, 1e9) for _ in range(n)]
    print(n, k, file=f)
    print(*c, file=f)

    init_dsu(n + 1)
    for _ in range(n - 1):
        u = randint(1, n - 1)
        v = randint(u + 1, n)
        while root(u) == root(v):
            u = randint(1, n - 1)
            v = randint(u + 1, n)
        print(u, v, file=f)

f.close()