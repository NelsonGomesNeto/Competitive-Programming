import os
from random import random, randint
os.system("g++ 2971Ordenação.cpp -o ./test")

amount = [0, 0, 2, 3, 4, 8]
t = 1
for n in range(len(amount)):
    for k in range(amount[n]):
        f = open("%d.in" % t, "w")
        print(n, file=f)
        a = [randint(-32768, 32767) for i in range(n)]
        print(*a, file=f)
        f.close()
        os.system("./test < %d.in > %d.out" % (t, t))
        t += 1