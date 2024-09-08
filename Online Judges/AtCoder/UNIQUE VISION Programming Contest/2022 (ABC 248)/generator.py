from random import randint
global parent, n
n = int(1e5)

def init():
    global parent
    parent = [-1]*n
def root(u):
    global parent
    if parent[u] < 0: return u
    parent[u] = root(parent[u])
    return parent[u]
def merge(u, v):
    global parent
    u, v = root(u), root(v)
    if u == v: return
    if parent[u] > parent[v]:
        u, v = v, u
    parent[u] += parent[v]
    parent[v] = u

print(n)
a = [40320 for i in range(1, n + 1)]
print(*a)

init()
edges = []
while len(edges) < n - 1:
    u = randint(0, n - 2)
    v = randint(u + 1, n - 1)
    while root(u) == root(v):
        u = randint(0, n - 2)
        v = randint(u + 1, n - 1)
    merge(u, v)
    edges.append((u, v))

for (u, v) in edges:
    print(u + 1, v + 1)