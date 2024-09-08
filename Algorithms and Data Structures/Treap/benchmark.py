import os
import time
os.system("g++ treap.cpp -o test -std=c++17 -O2")

times = []
for i in range(10):
    start_time = time.time()
    os.system("./test")
    times += [time.time() - start_time]
times.sort()
print(sum(times) / len(times), times)