def floodFill(graph, color, now, u):
    color[u] = now
    for v in graph[u]:
        if (color[v] == -1):
            if (not floodFill(graph, color, 1 - now, v)):
                return(0)
        elif (color[v] != 1 - now):
            return(0)
    return(1)

while (True):
    nodes = int(input())
    if (nodes == 0): break
    edges = int(input())
    graph = [[] for i in range(nodes)]
    for i in range(edges):
        u, v = map(int, input().split())
        graph[u] += [v]
        graph[v] += [u]

    color = [-1] * nodes
    if (not floodFill(graph, color, 0, 0)):
        print("NOT BICOLORABLE.")
    else:
        print("BICOLORABLE.")