import os
import time
from random import randint
from filecmp import cmp

os.system("g++ code.cpp -o test -std=c++17")

while True:
    f = open("big", "w")
    a = [randint(0, 9) for i in range(12)]
    

    f.close()

    start_time = time.time()
    os.system("./test < big")
    total_time = time.time() - start_time
    if total_time > 0.5:
        break
    print("Passou")