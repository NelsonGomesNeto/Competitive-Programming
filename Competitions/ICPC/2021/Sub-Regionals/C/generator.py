import os
from random import random, randint

f = open("big", "w")

max_b = int(1e4)
max_l = int(2e5)

B, L = max_b, max_l
print(B, L, file=f)
d = [randint(0, B - 1) for _ in range(L)]
print(*d, file=f)

f.close()