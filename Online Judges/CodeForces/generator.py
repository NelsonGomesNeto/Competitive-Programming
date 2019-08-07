from random import randint

f = open("big", "w")
n, m, k = int(2e5), int(2e5), int(2e5)
print(n, m, k, file=f)
graph = [{} for i in range(n)]
for i in range(m):
    u, v = randint(0, n - 1), randint(0, n - 1)
    while u == v or v in graph[u]:
        v = randint(0, n - 1)
    graph[u][v] = graph[v][u] = randint(1, int(1e9))
for u in range(n):
    for v in graph[u]:
        if u < v:
            print(u, v, graph[u][v], file=f)

f.close()