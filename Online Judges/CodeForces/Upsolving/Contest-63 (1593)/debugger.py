import os
from random import randint
from filecmp import cmp

os.system("g++ G.cpp -o test -std=c++17")
os.system("g++ bug.cpp -o bug -std=c++17")

while True:
    f = open("big", "w")

    t = 1
    print(t, file=f)

    for _ in range(t):
        n = 15
        s = ["()[]"[randint(0, 3)] for _ in range(n)]
        print(''.join(s), file=f)

        q = 100
        print(q, file=f)
        for _ in range(q):
            sz = 2*randint(1, n >> 1)
            l = randint(1, n - sz + 1)
            r = l + sz - 1
            assert((r - l) & 1)
            assert(l < r)
            assert(r <= n)
            print(l, r, file=f)

    f.close()

    os.system("./test < big > my")
    os.system("./bug < big > cor")
    if not cmp("my", "cor"):
        break
    print("Passou")