import os
from random import random, randint
from filecmp import cmp
os.system("g++ ./C.cpp -o ./test")

while True:
    f = open("big", "w")
    n, m = randint(1, 5), randint(1, 5)
    k = n * m
    print(n, m, k, file=f)
    for i in range(n):
        for j in range(m):
            print(i + 1, j + 1, file=f)
    for i in range(k):
        print(randint(1, n), randint(1, m), file=f)
    f.close()
    os.system("./test < big > out")
    if cmp("out", "unwanted"):
        break
    print("passou")