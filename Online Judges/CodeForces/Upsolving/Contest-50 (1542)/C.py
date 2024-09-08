from math import sqrt

mod = int(1e9 + 7)

def inv(x):
    return pow(x, mod - 2, mod)

t = int(input())
for tt in range(t):
    n = int(input())

    lol = int(n * (1 + 2*sqrt(5) + 5))
    ans = lol * inv(4) % mod
    print(ans)