import os
from random import random, randint

test_cases = int(1e2)
with open("big", "w") as f:
    print(test_cases, file=f)
    for t in range(1, test_cases + 1):
        n, m = 7, 7
        print(n, m, file=f)
        for _ in range(n):
            print("#"*m, file=f)