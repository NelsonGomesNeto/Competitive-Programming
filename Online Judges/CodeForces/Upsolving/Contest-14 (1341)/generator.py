from random import randint

n = int(1e4 - 1)
m = int(1e4)
g = int(1e3)

f = open("big", "w")
print(n, m, file=f)
d = list(range(0, n + 1))
print(*d, file=f)
print(g, g, file=f)