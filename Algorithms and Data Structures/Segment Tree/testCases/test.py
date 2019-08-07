import os
from random import randint, random
from filecmp import cmp
# os.system("g++ naive.cpp -o test")
os.system("g++ ./../segmentTree.cpp -o test -std=c++17 -O2 -w")
os.system("g++ ./../iterativeSegmentTree.cpp -o test2 -std=c++17 -O2 -w")

f = open("in", "w")
arraySize = int(input())
array = []
for i in range(arraySize): array += [randint(-1000, 1000)]
print(arraySize, file=f)
print(*array, file=f)

queries = int(input())
for i in range(queries):
    kind = randint(0, 1)
    lo = randint(0, arraySize - 1)
    hi = randint(lo, arraySize - 1)
    if (kind == 0):
        print("Q", lo, hi, file=f)
    else:
        print("U", lo, randint(-1000, 1000), file=f)
f.close()

os.system("time ./test < in > out")
os.system("time ./test2 < in > out2")
print("Verdict:", cmp("out", "out2"))
