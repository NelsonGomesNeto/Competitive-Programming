from heapq import *
inf = 2**33
DEBUG = 0

def minimum(a, b):
    if (a > b):
        return(b)
    return(a)

def dijkstra(graph, cost, visited, path, manaNeeded, start):
    cost[start] = manaNeeded[start]
    path[start] = start
    pq = []
    heappush(pq, [cost[start], start])
    while (pq):
        v = heappop(pq)[1]
        if (visited[v]): continue
        visited[v] = 1
        for u in graph[v]:
            if (cost[v] + manaNeeded[u] < cost[u]):
                cost[u] = cost[v] + manaNeeded[u]
                path[u] = v
                heappush(pq, [cost[u], u])

while (True):
    magics, saloons, galeries, monters = map(int, input().split())
    if (magics == 0 and saloons == 0 and galeries == 0 and monters == 0): break

    magic = []
    for i in range(magics):
        mana, damage = map(int, input().split())
        magic += [[mana, damage]]
    if (DEBUG == 1): print("Magic", magic)

    graph = [[] for i in range(saloons + 1)]
    for i in range(galeries):
        u, v = map(int, input().split())
        graph[u] += [v]
        graph[v] += [u]
    if (DEBUG == 1): print("Graph", graph)

    dp = [inf]*1001
    dp[0] = 0
    for life in range(1001):
        for mag in magic:
            if (life >= mag[1]):
                dp[life] = minimum(dp[life], dp[life - mag[1]] + mag[0])
            else:
                dp[life] = minimum(dp[life], mag[0])

    manaNeeded = [0]*(saloons + 1)
    for i in range(monters):
        place, life = map(int, input().split())
        manaNeeded[place] += dp[life]

    cost, visited, path = [inf]*(saloons + 1), [0]*(saloons + 1), [-1]*(saloons + 1)
    dijkstra(graph, cost, visited, path, manaNeeded, 1)

    if (cost[saloons] == inf):
        print(-1)
    else:
        print(cost[saloons])
