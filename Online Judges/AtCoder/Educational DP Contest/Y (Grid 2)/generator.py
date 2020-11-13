from random import randint

h, w = int(1e5), int(1e5)
n = int(3e3)
walls = []
for _ in range(n):
    i, j = randint(1, h), randint(1, w)
    while (i, j) in walls:
        i, j = randint(1, h), randint(1, w)
    walls += [(i, j)]
for i in range(n):
    print(*walls[i])