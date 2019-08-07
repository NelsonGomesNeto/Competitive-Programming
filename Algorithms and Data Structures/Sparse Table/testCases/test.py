import os, time
from random import randint
from filecmp import cmp
os.system("g++ ./../sparseTable.cpp -o test -std=c++17 -O2 -w")
os.system("g++ naive.cpp -o test2 -O2 -w")

f = open("in", "w")
arraySize = int(input())
a = []
for i in range(arraySize):
    a += [randint(-1000, 1000)]
print(arraySize, file=f)
print(*a, file=f)

queries = int(input())
for i in range(queries):
    lo = randint(0, arraySize - 1)
    hi = randint(lo, arraySize - 1)
    print(lo, hi, file=f)
f.close()

startTime = time.time()
os.system("./test < in > my")
print("sparseTable: %.5lf seconds" % (time.time() - startTime))

startTime = time.time()
os.system("./test2 < in > correct")
print("naive: %.5lf seconds" % (time.time() - startTime))

print("Verdict:", cmp("my", "correct"))
