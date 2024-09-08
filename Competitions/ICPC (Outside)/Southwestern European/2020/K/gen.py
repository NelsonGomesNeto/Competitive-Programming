from random import randint

n = int(3e5)

f = open("big", "w")
s = ""
for _ in range(n):
    s += chr(randint(ord('A'), ord('Z')))
print(s, file=f)
f.close()