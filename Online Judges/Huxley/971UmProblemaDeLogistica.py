from heapq import *
import sys
sys.setrecursionlimit(2**20)
DEBUG = 0
inf = 2**33

def prim(graph, cost, visited, start):
    total = 0
    cost[start] = 0
    pq = []
    heappush(pq, [cost[start], start])
    while (pq):
        c, v = heappop(pq)
        if (visited[v]): continue
        visited[v] = 1
        total += c
        for u in graph[v]:
            cost[u[0]] = u[1]
            heappush(pq, [cost[u[0]], u[0]])
    return(total)

tests, run = int(input()), 0
while (run < tests):
    if (run > 0):
        trash = input()
    numWarehouses = int(input())
    intToPoint, pointToInt = {}, {}
    for i in range(numWarehouses):
        point = list(map(int, input().split()))
        pointToInt[(point[0], point[1])] = i
        intToPoint[i] = point
    graph = [[] for i in range(numWarehouses)]
    for i in range(numWarehouses):
        for j in range(numWarehouses):
            dist = abs(intToPoint[i][0] - intToPoint[j][0]) + abs(intToPoint[i][1] - intToPoint[j][1])
            graph[i] += [[j, dist]]
    if (DEBUG):
        print("graph", graph)

    visited, cost = [0] * numWarehouses, [inf] * numWarehouses
    minCost = prim(graph, cost, visited, 0)

    print(run, ": ", minCost, sep='')
    run += 1