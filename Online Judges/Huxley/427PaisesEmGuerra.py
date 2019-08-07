from heapq import *
inf = 2**33

def floydWarshall(graph):
    dist = graph
    size = len(graph)
    for k in range(size):
        for i in range(size):
            for j in range(size):
                if (dist[i][k] + dist[k][j] < dist[i][j]):
                    dist[i][j] = dist[i][k] + dist[k][j]
    return(dist)

run = 0
while (True):
    cities, connections = map(int, input().split())
    if (cities == 0 and connections == 0):
        break
    if (run > 0):
        print()

    # dp = [[-1] * (cities + 1) for i in range(cities + 1)]
    graph = [[inf] * (cities + 1) for i in range(cities + 1)]
    for i in range(connections):
        u, v, c = map(int, input().split())
        if (graph[v][u] != inf):
            graph[u][v] = 0
            graph[v][u] = 0
        else:
            graph[u][v] = c

    dist = floydWarshall(graph)
    queries = int(input())
    for i in range(queries):
        begin, end = map(int, input().split())
        if (dist[begin][end] == inf):
            print("Nao e possivel entregar a carta")
        else:
            print(dist[begin][end])
    run += 1