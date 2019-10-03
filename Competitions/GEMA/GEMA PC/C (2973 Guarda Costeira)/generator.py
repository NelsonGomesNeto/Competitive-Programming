import os
from random import random, randint, shuffle
os.system("gcc 2973GuardaCosteira.c -o ./test -lm")

testCases = int(input())
options = list(range(0, 105))
shuffle(options)
f = open("originalIn", "r")
originalInput = f.readlines()
f.close()
f = open("originalOut", "r")
originalOutput = f.readlines()
f.close()
for t in range(1, testCases + 1):
    f = open("%d.in" % t, "w")
    print(originalInput[options[t]], end='', file=f)
    f.close()
    os.system("./test < %d.in > %d.out" % (t, t))