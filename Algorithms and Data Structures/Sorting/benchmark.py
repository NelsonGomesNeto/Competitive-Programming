import os
import time

def eval():
    start_time = time.time()
    os.system("./merge_sort < big_in")
    elapsed_time = time.time() - start_time
    return elapsed_time

N = int(1e3)
time_sum = 0
for _ in range(N):
    time_sum += eval()
average_time = time_sum / N
print(average_time)
