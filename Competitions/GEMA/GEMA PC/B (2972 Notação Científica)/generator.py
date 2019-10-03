import os
from random import random, randint
os.system("g++ 2972NotaçãoCientífica.cpp -o ./test")

testCases = int(input())
for t in range(1, testCases + 1):
    f = open("%d.in" % t, "w")
    x = random() * 10**10
    print(x, file=f)
    f.close()
    os.system("./test < %d.in > %d.out" % (t, t))