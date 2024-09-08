from queue import *
DEBUG = 0

def topologicalSortBFS(graph):
    inDegree = [0] * len(graph)
    for u in graph:
        for v in u:
            inDegree[v] += 1
    if (DEBUG):
        print(inDegree)
    queue = Queue()
    for i, quantity in enumerate(inDegree):
        if (quantity == 0):
            queue.put(i)

    answer, counter = [], 0
    while(not queue.empty()):
        curr = queue.get()
        #print("now", curr)
        answer += [curr]

        for u in graph[curr]:
            inDegree[u] -= 1
            if (inDegree[u] == 0):
                queue.put(u)

        counter += 1

    if (counter != len(graph)):
        return([])
    else:
        return(answer)

run = 0
while (True):
    friendsSize = int(input())
    if (friendsSize == 0):
        break
    friends = list(input().split())
    stringToInt = dict(zip(friends, range(0, friendsSize)))
    intToString = dict(zip(range(0, friendsSize), friends))
    if (DEBUG):
        print(stringToInt, intToString)

    graph = [[] for i in range(friendsSize)]
    for i in range(friendsSize):
        line = input().split()
        u, uFriends = line[0], line[1:]
        for v in uFriends[1:]:
            graph[stringToInt[v]] += [stringToInt[u]]

    if (DEBUG):
        print(graph)
        for i, u in enumerate(graph):
            print(intToString[i], end='')
            for v in u:
                print('->', intToString[v], end = ' ')
            print()

    if (run > 0):
        print()
    run += 1
    print("Teste", run)
    answer = topologicalSortBFS(graph)
    if (len(answer) == 0):
        print("impossivel")
    else:
        #answer.reverse()
        print(intToString[answer[0]], end='')
        for i in answer[1:]:
            print(' ', intToString[i], sep='', end='')
        print()

    # Do BFS Topological Sort!!!!
