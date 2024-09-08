from random import randint

n = 500
print(n)
costs = [[randint(1, int(1e9)) for j in range(n)] for i in range(n)]
for line in costs:
    print(*line)