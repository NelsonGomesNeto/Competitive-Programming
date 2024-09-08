from random import randint

f = open("big", "w")
for _ in range(int(1e4)):
    mx = int(1e9)
    print(randint(1, mx), randint(1, mx), randint(1, mx), file=f)
f.close()