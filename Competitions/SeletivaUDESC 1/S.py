n = int(input())
for i in range(n):
    a, b = map(int, input().split())
    print("Caso #%d:" % (i + 1), (b - a + 1) * (a + b) // 2)