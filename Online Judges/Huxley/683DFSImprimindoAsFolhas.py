def dfs(graph, u, leafs):
    if (len(graph[u]) == 0): leafs.add(u)
    for v in graph[u]:
        dfs(graph, v, leafs)

while (True):
    try:
        lines = int(input())
    except:
        break
    graph = {}
    for i in range(lines):
        u, v = input().split()
        if (u not in graph): graph[u] = []
        if (v not in graph): graph[v] = []
        graph[u] += [v]

    allLeafs, done = [], 0
    while (len(graph)):
        leafs = set()
        for i in graph:
            dfs(graph, i, leafs)
        for l in leafs:
            for i in graph:
                if (l in graph[i]):
                    graph[i].remove(l)
            del graph[l]
        allLeafs += [sorted(leafs)]
        done += len(leafs)
    for l in allLeafs:
        for i in l:
            print(i)
