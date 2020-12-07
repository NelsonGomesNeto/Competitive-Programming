from math import ceil
from decimal import Decimal

def gcd(a, b):
    if (a == 0):
        return b, 0, 1
    d, x1, y1 = gcd(b%a, a)
    x = y1 - (b // a) * x1
    y = x1
    return d, x, y

def find_any_solution(a, b, c):
    if (a < 0): a = -a
    if (b < 0): b = -b
    g, x, y = gcd(a, b)
    if (c % g):
        return False, 0, 0, 0
    x *= c // g
    y *= c // g
    if (a < 0): x = -x
    if (b < 0): y = -y
    return True, x, y, g

n, p, w, d = list(map(int, input().split()))

can, x, y, g = find_any_solution(w, d, p)
if (can):
    dx, dy = d // g, w // g
    while (x < 0):
        needed = int(ceil(-x / dx))
        x += needed * dx
        y -= needed * dy
    while (y < 0):
        needed = int(ceil(-y / dy))
        x -= needed * dx
        y += needed * dy

    if (x + y > n):
        lo, hi = 0, n
        while (lo < hi):
            mid = (lo + hi) >> 1
            if (x + mid*dx + y - mid*dy <= n): hi = mid
            else: lo = mid + 1
        x += lo*dx
        y -= lo*dy
        # if (x >= y):
        #     needed = int(ceil((x - n) / dx))
        #     x -= needed * dx
        #     y += needed * dy
        # else:
        #     needed = int(ceil((y - n) / dy))
        #     x += needed * dx
        #     y -= needed * dy
    # while ((x + y > n or x < 0) and y >= 0):
    #     x += dx
    #     y -= dy
    # while ((x + y > n or y < 0) and x >= 0):
    #     x -= dx
    #     y += dy
    x, y, z = int(x), int(y), int(n - (x + y))
    if (x + y > n or x < 0 or y < 0): print("-1")
    else: print(x, y, z)
else:
    print("-1")
