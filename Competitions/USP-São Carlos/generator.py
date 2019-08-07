import os
import filecmp
from collections import deque
os.system("g++ lol.cpp -o auxTest -std=c++11")

def dequeToNum(num):
    n = int(num.pop())
    pot = 10
    while (num):
        n += int(num.pop()) * pot
        pot *= 10
    return(n)

def ans(num):
    size = len(str(num))
    start = num
    num = deque(str(num))
    for i in range(size):
        num.rotate(1)
        newNum = dequeToNum(num.copy())
        if (start > newNum):
            return("No")
    return("Yes")

for i in range(10000):
    f = open("aux.in", "w")
    size = len(str(i))
    print(size, file=f)
    print(i, file=f)
    f.close()
    f = open("ans.out", "w")
    print(ans(i), file=f)
    f.close()
    os.system("./auxTest < aux.in > aux.out")
    if (not filecmp.cmp("aux.out", "ans.out")):
        print("Wrong:", i)
        print("Was:")
        os.system("cat aux.out")
        print("Should be:")
        os.system("cat ans.out")
