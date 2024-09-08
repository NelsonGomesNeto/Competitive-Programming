from heapq import *
inf = 2**33

def dijkstra(graph, cost, start, end):
    cost[start] = [0, 0]
    pq = []
    heappush(pq, [0, start, 0])
    while (pq):
        prevC, v, even = heappop(pq)
        if (prevC > cost[v][even]): continue
        for u, c in graph[v]:
            if (cost[v][even] + c < cost[u][1 - even]):
                cost[u][1 - even] = cost[v][even] + c
                heappush(pq, [cost[u][1 - even], u, 1 - even])

cities, streets = map(int, input().split())
graph = [[] for i in range(cities + 1)]
for i in range(streets):
    u, v, c = map(int, input().split())
    graph[u] += [[v, c]]
    graph[v] += [[u, c]]

cost = [[inf, inf] for i in range(cities + 1)]
dijkstra(graph, cost, 1, cities)

if (cost[cities][0] == inf):
    print(-1)
else:
    print(cost[cities][0])
