from heapq import *
inf = 2**33

def dijkstra(graph, monster, cost, visited, start, end):
    cost[start][0] = 0
    pq = []
    heappush(pq, [cost[start][0], start])
    while (pq):
        time, v = heappop(pq)
        #print(time, v)
        for u in graph[v]:
            if ((time + 1) % monster[u] != 0):
                if (time + 1 < cost[u][(time + 1) % (max(monster) + 1)]):
                    cost[u][(time + 1) % (max(monster) + 1)] = time + 1
                    heappush(pq, [time + 1, u])

#main
rooms, start, end, corridors = map(int, input().split())
monster = list(map(int, input().split()))
graph = [[] for i in range(rooms)]
for i in range(corridors):
    u, v = map(int, input().split())
    graph[u] += [v]
    #graph[v] += [u]
cost, visited = [[inf] * (max(monster) + 1) for i in range(rooms)], [0] * rooms
dijkstra(graph, monster, cost, visited, start, end)
#print(visited)
#print(cost)
#print(cost[end])
if (min(cost[end]) == inf):
    print("Araragi morreu")
else:
    print(min(cost[end]), "minutos")