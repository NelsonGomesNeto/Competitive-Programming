import os
import time
from filecmp import cmp
os.system("g++ .cpp -o test -std=c++17 -O2")

for i in range(1, len(os.listdir("input")) + 1):
    startTime = time.time()
    os.system("./test < input/_%d > out" % i)
    print(i, cmp("out", "output/_%d" % i), time.time() - startTime)