def dfs(graph, visited, start):
    visited[start] = 1
    total = 0
    for v in graph[start]:
        if (not visited[v]):
            total = max(total, dfs(graph, visited, v) + 1)
    return(total)

size = int(input())
graph = [[] for i in range(size + 1)]
for i in range(size - 1):
    u, v = map(int, input().split())
    graph[v] += [u]
    graph[u] += [v]

biggest = 0
for i in range(1, size + 1):
    if (len(graph[i]) == 1):
        visited = [0] * (size + 1)
        biggest = max(biggest, dfs(graph, visited, i))

print(biggest)