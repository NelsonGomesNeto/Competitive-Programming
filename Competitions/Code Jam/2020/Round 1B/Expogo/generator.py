from random import randint

maxX = int(100)

f = open("big", "w")
t = 100
print(t, file=f)
for i in range(t):
    x, y = randint(-maxX, maxX), randint(-maxX, maxX)
    print(x, y, file=f)
f.close()