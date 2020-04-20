import os
from random import random, randint
os.system("g++ ./../.cpp -o ./../test")

testCases = int(input())
for t in range(1, testCases + 1):
    f = open("%d.in" % t, "w")
    
    f.close()
    os.system("./../test < %d.in > %d.out" % (t, t))