DEBUG = 0
discoveryTime = [0]

def tarjan(graph, articulation, visited, low, discovery, parent, u):
    children = 0
    discovery[u], low[u] = discoveryTime[0], discoveryTime[0]
    discoveryTime[0] += 1
    visited[u] = 1
    for v in graph[u]:
        if (visited[v] == 0):
            parent[v] = u
            children += 1
            tarjan(graph, articulation, visited, low, discovery, parent, v)
            isRoot = (parent[u] == -1)
            if (isRoot and children > 1):
                articulation[u] = 1
            elif (not isRoot and discovery[u] <= low[v]):
                articulation[u] = 1
            low[u] = min(low[u], low[v])
        elif (v != parent[u]):
            low[u] = min(low[u], discovery[v])

while (True):
    places = int(input())
    if (places == 0): break
    graph = [[] for i in range(places + 1)]
    while (True):
        connection = list(map(int, input().split()))
        if (connection[0] == 0): break
        graph[connection[0]] += connection[1:]
        for u in connection[1:]:
            graph[u] += [connection[0]]
    if (DEBUG):
        print("graph", graph)

    visited, discovery = [0] * (places + 1), [0] * (places + 1)
    low, parent = [0] * (places + 1), [-1] * (places + 1)
    articulation = [0] * (places + 1)
    discoveryTime[0] = 0
    for i in range(places + 1):
        if (visited[i] == 0):
            tarjan(graph, articulation, visited, low, discovery, parent, i)

    if (DEBUG):
        print(visited, articulation)
    criticalPoints = sum(articulation)
    print(criticalPoints)
