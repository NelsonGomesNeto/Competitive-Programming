import sys
sys.setrecursionlimit(2**20)

def hasCycle(graph, visited, start, parent):
    visited[start] = 1
    for u in graph[start]:
        if (visited[u] == 1 and u != parent):
            return(1)
        elif (visited[u] == 0 and hasCycle(graph, visited, u, start)):
            return(1)
    visited[start] = 2
    return(0)

case = 1
while (True):
    try:
        if (case > 1):
            trash = input()
        vertices, edges = map(int, input().split())
    except:
        break
    
    graph = [[] for i in range(vertices)]
    for i in range(edges):
        u, v = map(int, input().split())
        graph[u] += [v]
        graph[v] += [u]

    visited = [0] * vertices
    print(case, hasCycle(graph, visited, u, -1))
    case += 1