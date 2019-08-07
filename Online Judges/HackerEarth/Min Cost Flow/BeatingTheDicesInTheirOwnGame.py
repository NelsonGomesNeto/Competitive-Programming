from copy import deepcopy
inf = 1<<20

def bellmannFord(graph, prev, source, target):
    cost = {}
    for i in graph: cost[i] = inf
    cost[source] = 0
    for i in range(len(graph) - 1):
        done = 0
        for u in graph:
            for v in graph[u]:
                if (graph[u][v][0] and cost[u] + graph[u][v][1] < cost[v]):
                    cost[v] = cost[u] + graph[u][v][1]
                    prev[v] = u
                    done = 1
        if (done == 0): break
    return(cost[target] != inf)

def minCostFlow(graph, source, target):
    minCost, maxFlow = 0, 0
    prev = {}
    for i in graph: prev[i] = "-"
    while (bellmannFord(graph, prev, source, target)):
        v, flow = target, inf
        while (v != source):
            flow = min(flow, graph[prev[v]][v][0])
            v = prev[v]
        maxFlow += flow

        v = target
        while (v != source):
            graph[prev[v]][v][0] -= flow;
            graph[v][prev[v]][0] += flow
            minCost += flow * graph[prev[v]][v][1]
            v = prev[v]

    return(minCost, maxFlow)

def printGraph(graph):
    for u in sorted(graph):
        print(u, end='')
        for v in sorted(graph[u]):
            print(" ->", (v, graph[u][v]), end='')
        print()

def addEdge(graph, u, v, f, c):
    if (u not in graph): graph[u] = {}
    if (v not in graph): graph[v] = {}
    graph[u][v] = [f, c]
    graph[v][u] = [0, -c]

graph = {}
n = int(input())
source, target = "source", "target"
done = set()
for i in range(1, n + 1):
    die = "d_%d" % i
    addEdge(graph, source, die, 1, 0)
    line = list(map(int, input().split()))
    for j in range(line[0]):
        face, c = "f_%d" % line[2 * j + 1], line[2* j + 2]
        addEdge(graph, die, face, 1, c)
        if (face not in done):
            addEdge(graph, face, target, 1, 0)
            done.add(face)

# copyGraph = deepcopy(graph)
q = int(input())
for i in range(q):
    # printGraph(graph)
    faces = list(map(int, input().split()))
    minCostFlow(graph, target, source)
    for face in graph[target]:
        graph[face][target] = [0, 0]
        graph[target][face] = [0, 0]
    for f in faces:
        face = "f_%d" % f
        graph[face][target] = [1, 0]
        graph[target][face] = [0, 0]
    minCost, maxFlow = minCostFlow(graph, source, target)
    if (maxFlow < n): print(-1)
    else: print(minCost)
    # graph = deepcopy(copyGraph)
