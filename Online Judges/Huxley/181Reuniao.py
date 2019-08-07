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

cities, connections = map(int, input().split())
graph = [[inf] * cities for i in range(cities)]
for i in range(connections):
    u, v, c = map(int, input().split())
    graph[u][v] = c
    graph[v][u] = c

dist = floydWarshall(graph)
minimum = inf
for i in dist:
    minimum = min(minimum, max(i))
print(minimum)