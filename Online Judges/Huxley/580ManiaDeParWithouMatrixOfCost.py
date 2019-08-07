from heapq import *
inf = 2**33

def dijkstra(graph, cost, visited, start, end):
    cost[start] = 0
    pq = []
    heappush(pq, [cost[start], start, 0])
    while (pq):
        time, v, paid = heappop(pq)
        if (visited[v] == 2): continue
        visited[v] += paid
        for u in graph[v]:
            if (((u[0] == end and 1 - paid == 0) or (u[0] != end)) and time + u[1] < cost[u[0]]):
                cost[u[0]] = time + u[1]
            heappush(pq, [time + u[1], u[0], 1 - paid])

cities, streets = map(int, input().split())
graph = [[] for i in range(cities + 1)]
for i in range(streets):
    u, v, c = map(int, input().split())
    graph[u] += [[v, c]]
    graph[v] += [[u, c]]

cost, visited = [inf] * (cities + 1), [0] * (cities + 1)
dijkstra(graph, cost, visited, 1, cities)

if (cost[cities] == inf):
    print(-1)
else:
    print(cost[cities])
