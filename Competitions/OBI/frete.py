from heapq import *

def dijkstra(graph, cost, visited, path, start):
    cost[start] = 0
    queue = []
    path[start] = start
    heappush(queue, [cost[start], start])
    while (queue):
        v = heappop(queue)[1]
        for u in graph[v]:
            if (cost[v] + u[1] < cost[u[0]]):
                cost[u[0]] = cost[v] + u[1]
                path[u[0]] = v
                heappush(queue, [cost[u[0]], u[0]])

cities, connections = map(int, input().split())
#print(cities, connections)

graph = [[] for i in range(cities + 1)]
for i in range(connections):
    u, v, c = map(int, input().split())
    graph[u] += [[v, c]]
    graph[v] += [[u, c]]
#print("Graph:", graph)

cost, visited, path = [9999999] * (cities + 1), [0] * (cities + 1), [-1] * (cities + 1)
dijkstra(graph, cost, visited, path, 1)
#print("Cost:", cost)
#print("Path:", path)

print(cost[cities])
