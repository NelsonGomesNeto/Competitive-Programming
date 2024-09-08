from random import randint

f = open("big", "w")
t = 100
print(t, file=f)
for _ in range(t):
    s = bin(randint(1, 1 << 100))[2:]
    e = bin(randint(1, 1 << 100))[2:]
    print(s, e, file=f)
f.close()