import os
from random import random, randint, shuffle
os.system("g++ 2975Melancia.cpp -o ./test")

testCases = int(input())
options = list(range(0, 20))
shuffle(options)
f = open("originalIn", "r")
originalInput = f.readlines()
f.close()
for t in range(1, testCases + 1):
    f = open("%d.in" % t, "w")
    print(originalInput[options[t - 1]], end='', file=f)
    f.close()
    os.system("./test < %d.in > %d.out" % (t, t))