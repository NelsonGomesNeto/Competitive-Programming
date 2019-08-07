from queue import *
DEBUG = 0

def khan(graph):
    inDegree = [0] * len(graph)
    for u in graph:
        for v in u:
            inDegree[v] += 1

    queue = Queue()
    for i, quantity in enumerate(inDegree):
        if (quantity == 0):
            queue.put(i)

    answer = []
    while (not queue.empty()):
        node = queue.get()
        answer += [node]
        for u in graph[node]:
            inDegree[u] -= 1
            if (inDegree[u] == 0):
                queue.put(u)
    return(answer)

case = 1
while (True):
    if (case > 1):
        print()

    friends = int(input())
    if (friends == 0): break
    friends = list(input().split())
    stringToInt, intToString = dict(zip(friends, range(0, len(friends)))), dict(zip(range(0, len(friends)), friends))
    graph = [[] for i in range(len(friends))]
    for i in range(len(friends)):
        line = list(input().split())
        #print(line)
        for j in line[2:]:
            graph[stringToInt[j]] += [stringToInt[line[0]]]
    if (DEBUG):
        print("stringToInt", stringToInt)
        print("intToString", intToString)
        print("graph", graph)

    answer = khan(graph)
    print("Teste", case)
    if (len(answer) < len(graph)):
        print("impossivel")
    else:
        print(' '.join(intToString[x] for x in answer))
        #print(*[intToString[x] for x in answer])
    case += 1
