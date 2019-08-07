inf = 2**33

def grade(graph, a, b, dp):
    if (a == b): return(0)
    a1, a2 = inf, inf
    if (a == -1 or b == -1): return(inf)
    if (dp[graph[a][0]][b] == -1):
        dp[graph[a][0]][b] = grade(graph, graph[a][0], b, dp)
    a1 = dp[graph[a][0]][b]
    if (dp[a][graph[b][0]] == -1):
        dp[a][graph[b][0]] = grade(graph, a, graph[b][0], dp)
    a2 = dp[a][graph[b][0]]
    if (a1 > a2):
        a1 = a2
    return(1 + a1)

def position(preGraph, name):
    for j, i in enumerate(preGraph):
        if (name in i):
            return(j)
    return(inf)

relations = int(input())
stringToInt, intToString = {}, {}
preGraph = []
people = 0
for i in range(relations):
    u, v = input().split()
    preGraph += [[u, v]]
    if (u not in stringToInt):
        stringToInt[u] = people
        intToString[people] = u
        people += 1
    if (v not in stringToInt):
        stringToInt[v] = people
        intToString[people] = v
        people += 1
graph = [[-1] for i in range(people)]
for line in preGraph:
    graph[stringToInt[line[1]]][0] = stringToInt[line[0]]

dp = [[-1] * people for i in range(people)]
best = [0, "zzzzzzzzzzzzzzzzzzzzzz", "zzzzzzzzzzzzzzzzzzzzzz"]
for i in stringToInt:
    for j in stringToInt:
        if (dp[stringToInt[i]][stringToInt[j]] == -1):
            dp[stringToInt[i]][stringToInt[j]] = grade(graph, stringToInt[i], stringToInt[j], dp)
        aux = dp[stringToInt[i]][stringToInt[j]]
        #if (aux > inf - 1000):
            #aux = 0
        if (aux > best[0] or (aux == best[0] and (position(preGraph, i) < position(preGraph, best[1]) or (position(preGraph, i) == position(preGraph, best[1]) and position(preGraph, j) < position(preGraph, best[2]))))):
            best = [aux, i, j]

names = [best[1], best[2]]
names.sort()
answer = [names[0], names[1], best[0]]
print(*answer)