import os
from time import sleep
from random import randint

# os.system("./debug_build.sh")

while True:
    with open("ebig", "w") as f:
        n = int(1e5)
        a = [randint(1, n) for _ in range(n)]
        queries = []
        for i in range(n):
            for t in range(int(1e9), int(1e9) - 1, -1):
                queries.append((i + 1, t))
        print(n, len(queries), file=f)
        print(*a, file=f)
        for (bi, ti) in queries:
            print(ti, bi, file=f)
    break
    if os.system("./p < ebig") != 0:
        break