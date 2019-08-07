from heapq import *
inf = 2**33

def dijkstra(graph, cost, visited, start):
    cost[start] = 0
    pq = []
    heappush(pq, [cost[start], start])
    while (pq):
        v = heappop(pq)[1]
        if (visited[v]): continue
        visited[v] = 1
        for u in graph[v]:
            if (cost[v] + 1 < cost[u]):
                cost[u] = cost[v] + 1
                heappush(pq, [cost[u], u])


tests = int(input())
while (tests > 0):
    islands, bridges = map(int, input().split())
    graph = [[] for i in range(islands + 1)]
    for i in range(bridges):
        u, v = map(int, input().split())
        graph[u] += [v]
        graph[v] += [u]
    cost, visited = [inf] * (islands + 1), [0] * (islands + 1)
    dijkstra(graph, cost, visited, 1)
    if (cost[islands] == inf):
        print(-1)
    else:
        print(cost[islands])

    tests -= 1