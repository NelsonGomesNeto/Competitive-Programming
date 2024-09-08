import os
from random import random, randint

canvas_options = ".^#"

test_cases = 80
print(test_cases)

max_n = int(5)
for t in range(test_cases):
    n, m = max_n, max_n
    print(n, m)
    canvas = [[canvas_options[randint(0, 2)] for _ in range(m)] for _ in range(n)]
    for line in canvas:
        print(''.join(line))