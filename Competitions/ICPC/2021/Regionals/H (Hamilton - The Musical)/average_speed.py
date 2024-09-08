import os
import sys
from time import time

binary_name = sys.argv[1]

def get_run_time():
    start_time = time()
    os.system("%s < big > out" % binary_name)
    return time() - start_time

runs = 100
times = [get_run_time() for _ in range(runs)]
times.sort()

print(times[:5])