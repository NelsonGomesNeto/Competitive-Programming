from heapq import *
inf = int(1e9)

def dijkstra(source):
    cost[source] = 0
    pq = []
    heappush(pq, [cost[source], source])
    while pq:
        c, u = heappop(pq)
        if c > cost[u]:
            continue
        for v in graph[u]:
            if c + v[1] < cost[v[0]]:
                cost[v[0]] = c + v[1]
                prv[v[0]] = u
                heappush(pq, [cost[v[0]], v[0]])
    return cost

n, m = map(int, input().split())

graph = [[] for i in range(n)]
for i in range(m):
    u, v, c = map(int, input().split())
    u, v = u - 1, v - 1 # Just to index by 0
    graph[u] += [[v, c]]
    graph[v] += [[u, c]]

cost, prv = [inf] * n, [-1] * n
dijkstra(0)
print(cost[n - 1])
print(cost)
print(prv)