from random import randint

n = int(2e5)
for i in range(n):
    print(bin(randint(1, (1 << 61) -1))[2:])