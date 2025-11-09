def hehe(n: int) -> int:
    s = 0
    for i in range(n):
        for j in range(i + 1, n):
            s += 1
    return s

for i in range(100):
    print(hehe(i), i*(i - 1) // 2)