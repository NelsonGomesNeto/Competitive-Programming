import os
import subprocess
import time
from filecmp import cmp
subprocess.run(["g++", "code.cpp", "-o", "p", "-std=c++23", "-O2"])

execution_times = []
for i in range(1, len(os.listdir("input")) + 1):
    start_time = time.perf_counter()
    with open("input/C_%04d" % i, "r") as input_file, open("out", "w") as output_file:
        try:
            subprocess.run("./test", stdin=input_file, stdout=output_file, timeout=2)
        except subprocess.TimeoutExpired:
            print(f"TLE test_case {i}")
            break
        except Exception as e:
            print(f"RTE test_case {i} | error: {e}")
    execution_time = time.perf_counter() - start_time
    execution_times.append(execution_time)
    if not cmp("out", "output/C_%04d" % i):
        print(f"Failed test_case {i}")
        break
    else:
        print(f"Passed test_case {i}")

print("max(execution_times): ", max(execution_times))
