from heapq import heappush, heappop

def dijkstra():
    pq = []
    dist[0] = nodes[0]
    dist[1] = nodes[1]
    heappush(pq, (dist[0], 0))
    heappush(pq, (dist[1], 1))
    while pq:
        d, u = heappop(pq)
        if d > dist[u]: continue

        for v in graph[u]:
            if d + nodes[v] < dist[v]:
                dist[v] = d + nodes[v]
                prv[v] = u
                heappush(pq, (dist[v], v))
    return min(dist[vertices - 2 : vertices])

while True:
    try:
        tests = int(input())
    except EOFError:
        break

    for tt in range(1, tests + 1):
        n = int(input())
        vertices = 2 + 2*n + 2*n - 2 + 2

        nodes = []
        graph = [[] for _ in range(vertices)]

        e = list(map(int, input().split()))
        nodes += e
        for i in range(2):
            graph[i].append(2 + i*n)

        a = []
        for i in range(2):
            ai = list(map(int, input().split()))
            a += [ai]
            nodes += ai
            for j in range(n - 1):
                graph[2 + i*n + j].append(2 + i*n + j + 1)
                graph[2 + i*n + j].append(2 + 2*n + i*(n - 1) + j)
        graph[2 + n - 1].append(vertices - 2)
        graph[2 + n + n - 1].append(vertices - 1)

        t = []
        for i in range(2):
            ti = list(map(int, input().split()))
            t += [ti]
            nodes += ti
            for j in range(n - 1):
                graph[2 + 2*n + i*(n - 1) + j].append(2 + (1 - i)*n + j + 1)

        x = list(map(int, input().split()))
        nodes += x

        dist = [int(1e18) for _ in range(vertices)]
        prv = [-1 for _ in range(vertices)]

        ans = dijkstra()
        print(ans)
