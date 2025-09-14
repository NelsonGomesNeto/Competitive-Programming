import os
from random import random, randint
os.system("g++ 2978BitABit.cpp -o ./test")

instructions = ["CLEAR", "SET", "OR", "AND"]

def getRandomInstruction():
    pos = randint(0, 3)
    if (pos <= 1):
        return instructions[pos] + " " + str(randint(0, 31))
    return instructions[pos] + " " + str(randint(0, 31)) + " " + str(randint(0, 31))

testCases = int(input())
for t in range(1, testCases + 1):
    f = open("%d.in" % t, "w")
    k = randint(1, 100)
    for i in range(k):
        n = randint(1, 100)
        print(n, file=f)
        for s in range(n):
            print(getRandomInstruction(), file=f)
    print(0, file=f)
    f.close()
    os.system("./test < %d.in > %d.out" % (t, t))