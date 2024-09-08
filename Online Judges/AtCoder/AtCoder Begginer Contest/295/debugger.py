import os
from random import randint
from filecmp import cmp

os.system("g++ G.cpp -o test -std=c++17")
os.system("g++ bug.cpp -o bug -std=c++17")

visited = set()
def dfs(u):
    if u in visited:
        return []
    visited.add(u)
    ans = []
    for v in gs[u]:
        ans = dfs(v)
        ans.append(v)
    return ans

while True:
    f = open("big", "w")
    n = randint(2, 10)
    q = randint(5, 20)
    print(n, file=f)
    p = []
    gs = [[] for i in range(0, n + 1)]
    for i in range(1, n):
        pi = randint(1, i)
        p.append(pi)
        gs[pi].append(i + 1)
    print(n, p)
    print(gs)
    print(*p, file=f)
    print(q, file=f)
    for _ in range(q):
        op = randint(1, 2)
        if op == 1:
            u = randint(1, n)
            visited = set()
            reachable = dfs(u)
            while len(reachable) == 0:
                u = randint(1, n)
                visited = set()
                reachable = dfs(u)
            v = reachable[randint(0, len(reachable) - 1)]
            print(1, v, u, file=f)
        else:
            x = randint(1, n)
            print(2, x, file=f)
    f.close()

    print("started")
    os.system("./test < big > my")
    os.system("./bug < big > cor")
    if not cmp("my", "cor"):
        break
    print("Passou")