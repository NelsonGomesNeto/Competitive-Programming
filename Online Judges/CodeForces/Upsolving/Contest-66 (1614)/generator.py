from random import randint

max_n = int(2e5)
n, m = max_n, max_n
print(n, m)
for i in range(m):
    print(1 + i, 1 + i, randint(0, (1 << 30) - 1))