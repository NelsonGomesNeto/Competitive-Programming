def floodFill(graph, visited, start):
    s = 0
    if (not visited[start]):
        s += 1
        visited[start] = 1
        for v in graph[start]:
            s += floodFill(graph, visited, v)
    return(s)

size = int(input())
graph = [[] for i in range(size)]
for i in range(size - 1):
    v, u = map(int, input().split())
    v -= 1
    u -= 1
    graph[v] += [u]
    graph[u] += [v]

minimum = 9999999999
for i in range(size):
    for j in graph[i]:
        graph[i].remove(j)
        visited = [0] * size
        a = floodFill(graph, visited, i)
        b = floodFill(graph, visited, j)
        dif = abs(a - b)
        minimum = min(dif, minimum)
        graph[i] += [j]

print(minimum)
