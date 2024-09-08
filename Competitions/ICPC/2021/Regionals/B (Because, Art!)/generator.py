from random import random, randint

test_file = open("big", "w")
n = int(1e5)
maxX = int(1e4)
f = [randint(-maxX, 0) for _ in range(n)]
c = [randint(-maxX, 0) for _ in range(n)]
print(n, file=test_file)
print(*f, file=test_file)
print(*c, file=test_file)
