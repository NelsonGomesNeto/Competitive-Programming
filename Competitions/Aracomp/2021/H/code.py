from math import gcd

n = int(input())
for i in range(n):
    a, b = list(map(int, input().split()))
    g = a
    for bb in range(a + 1, b + 1):
        g = gcd(g, bb)
        if g == 1:
            break
    print(g)
