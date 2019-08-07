from heapq import *

def dijkstra(graph, cost, visited, path, start):
    cost[start] = 0
    queue = []
    path[start] = start
    heappush(queue, [cost[start], start])
    while (queue):
        v = heappop(queue)[1]
        if (not visited[v]):
            visited[v] = 1
            for u in graph[v]:
                if (cost[v] + u[1] < cost[u[0]]):
                    cost[u[0]] = cost[v] + u[1]
                    path[u[0]] = v
                    heappush(queue, [cost[u[0]], u[0]])


stations, connections = map(int, input().split())
print(stations, connections)

graph = [[] for i in range(stations)]
for i in range(connections):
    u, v, c = map(int, input().split())
    graph[u] += [[v, c]]
    graph[v] += [[u, c]]
#print("Graph:", graph)

cost, visited, path = [99999999] * stations, [0] * stations, [-1] * stations
for i in range(stations):
    if (path[i] == -1):
        dijkstra(graph, cost, visited, path, i)
        for i, j in enumerate(cost):
            if (j != 99999999 and len(graph[i]) > 2):
                print(i, sep='', end=' ')
        print()
