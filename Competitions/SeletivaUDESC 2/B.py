from math import sqrt
DEBUG = 0
inf = 1<<20

def floyd(dist):
    for k in sorted(dist):
        for i in sorted(dist):
            for j in sorted(dist):
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])

def distance(planets, i, j):
    x1, y1, z1 = planets[i]
    x2, y2, z2 = planets[j]
    return(sqrt((x1 - x2)**2 + (y1 - y2)**2 + (z1 - z2)**2))

t = int(input())
for r in range(1, t + 1):
    p = int(input())
    planets = {}
    for i in range(p):
        line = input().split()
        planets[line[0]] = list(map(int, line[1:]))
    if (DEBUG): print(planets)

    graph = {}
    for i in planets:
        graph[i] = {}
        for j in planets:
            graph[i][j] = distance(planets, i, j)

    connections = int(input())
    for i in range(connections):
        line = input().split()
        graph[line[0]][line[1]] = 0

    floyd(graph)

    print("Caso %d:" % r)
    queries = int(input())
    for q in range(queries):
        line = input().split()
        print("A distancia de", line[0], "para", line[1], "eh", round(graph[line[0]][line[1]]), "parsecs.")

# for(int i=1;i<=n;i++){
#         for(int j=1;j<=n;j++){
#             if(i==j) dist[i][j] = 0;
#             else if(adj[i][j]) dist[i][j] = adj[i][j];
#             else dist[i][j] = INF;
#         }
#     }