from heapq import *

def prim(graph):
    mst = [[] for i in range(len(graph))]
    visited = [0] * len(graph)
    pq = []
    cost = 0
    heappush(pq, [0, 0, -1])
    while (pq):
        c, u, prev = heappop(pq)
        if (visited[u]): continue
        visited[u] = 1
        cost += c
        if (prev != -1):
            mst[prev] += [[u, c]]
            mst[u] += [[prev, c]]
        for v, cc in graph[u]:
            heappush(pq, [cc, v, u])
    return(mst, cost)

def root(v):
    if (parent[v] < 0):
        return(v)
    else:
        parent[v] = root(parent[v])
        return(parent[v])

def isSameSet(v, u):
    return(root(v) == root(u))

def merge(v, u):
    v = root(v)
    u = root(u)
    if (v == u): return
    if (parent[u] < parent[v]):
        parent[u], parent[v] = parent[v], parent[u]
    parent[v] += parent[u]
    parent[u] = v

def setSize(v):
    return(-parent[root(v)])

def kruskal(edges, n):
    edges.sort()
    mst, cost = [[] for i in range(n)], 0
    for c, u, v in edges:
        if (not isSameSet(u, v)):
            merge(u, v)
            mst[u] += [[v, c]]
            mst[v] += [[u, c]]
            cost += c
    return(mst, cost)

n, m = map(int, input().split())
# graph = [[] for i in range(n)]
edges = []
for i in range(m):
    u, v, c = map(int, input().split())
    u, v = u - 1, v - 1
    # graph[u] += [[v, c]]
    # graph[v] += [[u, c]]
    edges += [[c, u, v]]
    edges += [[c, v, u]]

# mst, cost = prim(graph)
parent = [-1] * n
mst, cost = kruskal(edges, n)
print(cost)
