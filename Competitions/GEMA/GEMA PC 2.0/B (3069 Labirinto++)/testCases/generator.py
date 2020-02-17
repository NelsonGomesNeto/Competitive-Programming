import os
import sys
from random import random, randint, shuffle
sys.setrecursionlimit(2**30)
os.system("g++ ./../B.cpp -o ./../test")

maxN, maxT, maxC = int(1e3 - 1), int(1e3 - 1), int(1e3)
n, m, = 0, 0
maze = []
di, dj = [0, 0, 1, -1], [1, -1, 0, 0]


def valid(i, j):
    return i >= 0 and j >= 0 and i < n and j < m


def bt():
    global maze

    stack = [[0, 0]]
    while len(stack):
        i, j = stack.pop(-1)
        kk = list(range(4))
        shuffle(kk)
        for k in kk:
            if valid(i + 2*di[k], j + 2*dj[k]) and maze[i + 2*di[k]][j + 2*dj[k]] == '#':
                for d in range(2 + 1):
                    maze[i + d*di[k]][j + d*dj[k]] = '.'
                stack += [[i + 2*di[k], j + 2*dj[k]]]


def genMaze():
    global maze, n, m

    n = randint(1, maxN // 2)*2 + 1
    m = randint(1, maxN // 2)*2 + 1
    print(n, m, file=f)
    maze = [['#' for i in range(m)] for i in range(n)]
    try:
        bt()
    except Exception as e:
        print(e)
        exit(0)

    freed = []
    for i in range(n):
        for j in range(m):
            if maze[i][j] == '.':
                freed += [[i, j]]
    teleports = randint(0, min(maxT, len(freed)))
    tps = []
    for i in range(teleports):
        u, v, c = randint(0, len(freed) - 1), randint(0, len(freed) - 1), randint(0, maxC)
        tps += [[u, v, c]]
        maze[freed[u][0]][freed[u][1]] = 'o'
        maze[freed[v][0]][freed[v][1]] = 'o'

    for i in range(n):
        for j in range(m):
            print(maze[i][j], end='', file=f)
        print(file=f)

    print(teleports, file=f)
    for i in range(teleports):
        u, v, c = tps[i]
        print(freed[u][0] + 1, freed[u][1] + 1, freed[v][0] + 1, freed[v][1] + 1, c, file=f)
    print(solve())


def solve():
    global maze
    q = [[0, 0, 0]]
    while len(q):
        u = q.pop(0)
        if (u[0] == n - 1 and u[1] == m - 1):
            return u[2]
        for k in range(4):
            ni, nj = u[0] + di[k], u[1] + dj[k]
            if valid(ni, nj) and maze[ni][nj] != '#':
                maze[ni][nj] = '#'
                q += [[ni, nj, u[2] + 1]]
    return -1



testCases = int(input())
for t in range(1, testCases + 1):
    f = open("%d.in" % t, "w")
    genMaze()
    f.close()
    os.system("./../test < %d.in > %d.out" % (t, t))