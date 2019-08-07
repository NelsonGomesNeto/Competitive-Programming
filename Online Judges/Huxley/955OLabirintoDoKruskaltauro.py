from heapq import *
inf = 2**33
DEBUG = 0

def waitTime(period, time):
    return(period - time % period)

def dijkstra(graph, cost, start, period):
    for i in range(len(cost[start])):
        cost[start][i] = 0
    pq = []
    heappush(pq, [cost[start][0], start])
    while (pq):
        time, v = heappop(pq)
        for u in graph[v]:
            if (u[1] == 0 or time % u[1] == 0):
                if (time + 1 < cost[u[0]][(time + 1) % period]):
                    cost[u[0]][(time + 1) % period] = time + 1
                    heappush(pq, [time + 1, u[0]])
            else:
                timeToWait = waitTime(u[1], time)
                if (time + timeToWait + 1 < cost[u[0]][(time + timeToWait + 1) % period]):
                    cost[u[0]][(time + timeToWait + 1) % period] = time + timeToWait + 1
                    heappush(pq, [time + timeToWait + 1, u[0]])

tests = int(input())
run = -1
while (run < tests - 1):
    run += 1
    if (run != 0):
        qqq = input()
    y, x = map(int, input().split())
    #labyrinth = [[1 for i in range(x)] for i in range(y)]
    graph = [[] for i in range(x*y)]
    for i in range(y*x):
        #for j in range(x):
        line = input()
        for k in line:
            if k == 'N':
                #labyrinth[i - 1][j] = 0
                graph[i] += [[i - x, 0]]
            if k == 'E':
                #labyrinth[i][j + 1] = 0
                graph[i] += [[i + 1, 0]]
            if k == 'S':
                #labyrinth[i + 1][j] = 0
                graph[i] += [[i + x, 0]]
            if k == 'W':
                #labyrinth[i][j - 1] = 0
                graph[i] += [[i - 1, 0]]

    portals, period = map(int, input().split())
    for i in range(portals):
        ui, uj, vi, vj = map(int, input().split())
        graph[ui*x + uj] += [[vi*x + vj, period]]
    if (DEBUG == 1):
        for i in range(y):
            for j in range(x):
                print(i*x + j, "->", graph[i*x + j])
                #print(j, end=' ')
            print()

    cost = [[inf] * (period + 1) for i in range(x*y + 1)]
    dijkstra(graph, cost, 0, period)
    print(run, ": ", min(cost[x*y-1]), sep='')