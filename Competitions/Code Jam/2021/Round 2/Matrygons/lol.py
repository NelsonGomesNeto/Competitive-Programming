def hehe(n):
    sum = 0
    now = 3
    for _ in range(n):
        sum += now
        now *= 2
    return sum

for i in range(20):
    print(i, hehe(i))