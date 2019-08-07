import time, os
from random import randint

w1, w2 = 0, 0
while (True):
    f = open("in", "w")
    n, m = 5000, 30000
    print(n, m, file=f)
    for i in range(30000):
        print(randint(1, n), randint(1, n), randint(1, 1e9), file=f)
    f.close()
    s1 = time.time()
    os.system("./test < in > out")
    t1 = time.time() - s1

    if (t1 >= 1):
        print("FODEU", t1)
        s1 = time.time()
        os.system("./test < in > out")
        t1 = time.time() - s1
        if (t1 >= 1): break

    s2 = time.time()
    os.system("./test2 < in > out")
    t2 = time.time() - s2

    if (t1 <= t2): w1 += 1
    else: w2 += 1
    print("%.4g %.4g" % (t1, t2), w1, w2)
