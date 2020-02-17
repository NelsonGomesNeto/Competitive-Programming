import os
from math import sqrt, floor
from random import random, randint
os.system("g++ ./../F.cpp -o ./../test")

maxSize = int(1e3)
global table

def swap_block(u, v, horizontal):
    global table
    for i in range(sqrtn):
        for j in range(n):
            if horizontal:
                table[u*sqrtn + i][j], table[v*sqrtn + i][j] = table[v*sqrtn + i][j], table[u*sqrtn + i][j]
            else:
                table[j][u*sqrtn + i], table[j][v*sqrtn + i] = table[j][v*sqrtn + i], table[j][u*sqrtn + i]


def swap_line(sq, u, v, horizontal):
    global table
    for i in range(n):
        if horizontal:
            table[sq*sqrtn + u][i], table[sq*sqrtn + v][i] = table[sq*sqrtn + v][i], table[sq*sqrtn + u][i]
        else:
            table[i][sq*sqrtn + u], table[i][sq*sqrtn + v] = table[i][sq*sqrtn + v], table[i][sq*sqrtn + u]


testCases = int(input())
for t in range(1, testCases + 1):
    f = open("%d.in" % t, "w")
    sqrtn = randint(1, int(floor(sqrt(maxSize))))
    n = sqrtn*sqrtn
    print(n, file=f)
    table = [[0 for j in range(n)] for i in range(n)]
    valid = randint(0, 1)

    for i in range(n):
        shift = i // sqrtn + sqrtn * (i % sqrtn)
        for j in range(n):
            table[i][j] = 1 + (shift + j) % n
    for i in range(randint(0, n)):
        u = randint(0, sqrtn - 2)
        v = randint(u + 1, sqrtn - 1)
        swap_block(u, v, randint(0, 1))
    for i in range(randint(0, n)):
        sq = randint(0, sqrtn - 1)
        u = randint(0, sqrtn - 2)
        v = randint(u + 1, sqrtn - 1)
        swap_line(sq, u, v, randint(0, 1))

    if not valid:
        i, j = randint(0, n - 1), randint(0, n - 1)
        table[i][j] = randint(1, n)
    for i in range(n):
        print(*table[i], file=f)

    f.close()
    os.system("./../test < %d.in > %d.out" % (t, t))