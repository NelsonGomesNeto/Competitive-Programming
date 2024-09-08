from heapq import *
inf = 2**33

def prim(graph, visited, cost, start, airportCost):
    total = 0
    cost[start] = 0
    pq = []
    heappush(pq, [cost[start], start])
    while (pq):
        c, u = heappop(pq)
        if (visited[u]): continue
        visited[u] = 1
        total += c
        for v in graph[u]:
            cost[v[0]] = v[1]
            heappush(pq, [cost[v[0]], v[0]])
    return(total)


tests, case = int(input()), 1
while (case <= tests):
    locations, roads, airportCost = map(int, input().split())

    graph = [[] for i in range(locations)]
    for i in range(roads):
        u, v, c = map(int, input().split())
        u -= 1
        v -= 1
        if (c >= airportCost): continue
        graph[u] += [[v, c]]
        graph[v] += [[u, c]]

    price, airports = 0, 0
    visited = [0] * locations
    for i in range(locations):
        if (not visited[i]):
            cost = [inf] * locations
            price += prim(graph, visited, cost, i, airportCost) + airportCost
            airports += 1

    print("Case #%d:" % case, price, airports)
    case += 1