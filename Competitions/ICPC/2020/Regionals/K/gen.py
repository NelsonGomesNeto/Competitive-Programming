k = 750
n = int(1e4)
l = int(1e9)

f = open("big", "w")

print(k, l, file=f)
t = [[1 for j in range(k)] for i in range(k)]
for line in t:
    print(*line, file=f)
print(n, file=f)
p = [1 for i in range(n - 1)]
print(*p, file=f)

f.close()