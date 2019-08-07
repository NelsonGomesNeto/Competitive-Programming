def go(u, n):
    # print(u, n, participants)
    if (u <= n): return

    if (race[u][0] <= n and race[u][1] <= n):
        participants[u] += [[race[u][0], probability[race[u][0]][race[u][1]]]]
        participants[u] += [[race[u][1], probability[race[u][1]][race[u][0]]]]
        return

    go(race[u][0], n)
    go(race[u][1], n)

    if (race[u][0] <= n or race[u][1] <= n):
        win = 0
        competidor = race[u][0] if race[u][0] <= n else race[u][1]
        raceToDiscover = race[u][1] if race[u][0] <= n else race[u][0]
        for v in participants[raceToDiscover]:
            win += probability[competidor][v[0]] * v[1]
            participants[u] += [[v[0], probability[v[0]][competidor] * v[1]]]
        participants[u] += [[competidor, win]]
        return

    for v in participants[race[u][0]]:
        win = 0
        for w in participants[race[u][1]]:
            win += probability[v[0]][w[0]] * w[1] * v[1]
        participants[u] += [[v[0], win]]
    for w in participants[race[u][1]]:
        win = 0
        for v in participants[race[u][0]]:
            win += probability[w[0]][v[0]] * v[1] * w[1]
        participants[u] += [[w[0], win]]

while (True):
    n = int(input())
    if (n == 0): break
    probability = [[]]
    for i in range(n):
        probability += [[0] + list(map(float, input().split()))]
    # print(probability)

    tournament = []
    race, nextRace, participants = [-1] * (2 * n), [-1] * (2 * n), [[] for i in range(2 * n)]
    for i in range(n + 1, 2 * n):
        nowRace = list(map(int, input().split()))
        nextRace[nowRace[0]], nextRace[nowRace[1]] = i, i
        race[i] = nowRace
    # print(race[n+1:])

    root, at = 1, 1
    while (at != -1):
        root = at
        at = nextRace[at]
    go(root, n)

    for winner in participants[root]:
        if (winner[0] == 1):
            print("%.6lf" % winner[1])
            break