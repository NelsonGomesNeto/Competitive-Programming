import os
from random import random, randint

max_n = int(3e3)
max_m = max_n * (max_n - 1) >> 1
max_q = int(2e5)
max_c = int(1e9)
test_cases = 1

print(test_cases)
for t in range(test_cases):
    n, m, q = max_n, max_m, max_q
    print(n, m, q)
    has = set()
    # for i in range(m):
    #     u = randint(1, n - 1)
    #     v = randint(u + 1, n)
    #     while (u, v) in has:
    #         u = randint(1, n - 1)
    #         v = randint(u + 1, n)
    #     has.add((u, v))
    #     has.add((v, u))
    #     c = randint(1, max_c)
    #     print(u, v, c)
    hehe = 0
    for i in range(1, n):
        for j in range(i + 1, n + 1):
            u, v = i, j
            c = randint(1, max_c)
            print(u, v, c)
            hehe += 1
    assert(hehe == m)
    for i in range(q):
        u = randint(1, n - 1)
        v = randint(u + 1, n)
        print(u, v)
