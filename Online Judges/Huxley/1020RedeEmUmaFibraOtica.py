def root(parent, v):
    if (parent[v] < 0):
        return(v)
    else:
        parent[v] = root(parent, parent[v])
        return(parent[v])

def isSameSet(parent, v, u):
    return(root(parent, v) == root(parent, u))

def merge(parent, v, u):
    v = root(parent, v)
    u = root(parent, u)
    if (v == u): return

    if (parent[v] < parent[u]):
        parent[v], parent[u] = parent[u], parent[v]

    parent[v] += parent[u]
    parent[u] = v

def setSize(parent, v):
    return(-1 * parent[root(parent, v)])

def bfs(graph, source, cost, visited):
    queue = [[source, 0]]
    while (queue):
        u, c = queue.pop(0)
        if (visited[u]): continue
        cost[u] = c
        visited[u] = 1
        for v, newCost in graph[u]:
            queue += [[v, c + newCost]]

vertices, edges, speed = map(int, input().split())
graph = [[] for i in range(vertices)]
allEdges = []
for i in range(edges):
    u, v, c = map(int, input().split())
    graph[u] += [[v, c]]
    graph[v] += [[u, c]]
    allEdges += [[c, u, v]]
allEdges.sort()
parent = [-1] * len(allEdges)

mst, minCost = [[] for i in range(vertices)], 0
for c, u, v in allEdges:
    if (not isSameSet(parent, v, u)):
        mst[u] += [[v, c]]
        mst[v] += [[u, c]]
        merge(parent, v, u)
        minCost += c

cost, visited = [0] * vertices, [0] * vertices
bfs(mst, 0, cost, visited)

print("########################")
print("Minimum Cost:\n", minCost, sep='')
print("########################")
print("Connections:")
done = [[0] * vertices for i in range(vertices)]
for i in range(len(mst)):
    for j in sorted(mst[i]):
        if (done[i][j[0]] == 0):
            done[j[0]][i] = 1
            print(i, j[0])
print("########################")
print("Pings:")
for i in range(1, vertices):
    print("%d: %.3lf" % (i, (cost[i] * 2) / speed), sep='')
print("########################")
