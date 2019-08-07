from heapq import *
inf = 2**33
DEBUG = 0

def dijkstra(graph, cost, start):
    cost[origin] = [0] * 255
    pq = []
    heappush(pq, [cost[start][0], start, '\0'])
    while (pq):
        c, v, prev = heappop(pq)
        for u in graph[v]:
            if (u[2] != prev and c + u[1] < cost[u[0]][ord(u[2])]):
                cost[u[0]][ord(u[2])] = c + u[1]
                heappush(pq, [cost[u[0]][ord(u[2])], u[0], u[2]])

while (True):
    words = int(input())
    if (words == 0): break

    origin, destination = input().split()
    graph = {}
    graph[origin], graph[destination] = [], []
    for i in range(words):
        u, v, word = input().split()
        if (u not in graph): graph[u] = []
        if (v not in graph): graph[v] = []
        graph[u] += [[v, len(word), word[0]]]
        graph[v] += [[u, len(word), word[0]]]

    cost, visited = {}, {}
    for i in graph:
        cost[i] = [inf] * 255
    dijkstra(graph, cost, origin)
    if (min(cost[destination]) == inf):
        print("impossivel")
    else:
        print(min(cost[destination]))