from random import randint

f = open("big", "w")
n = 3000
print(n, file=f)
for _ in range(n):
    print(*[randint(1, int(1e9)) for _ in range(5)], file=f)
f.close()