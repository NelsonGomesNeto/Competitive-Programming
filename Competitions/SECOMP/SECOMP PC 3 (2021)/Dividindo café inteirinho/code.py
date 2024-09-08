def required(x: int):
    return sum([a[i]*b[i]*x for i in range(n)])

while True:
    try:
        t = int(input())
    except EOFError:
        break

    for tt in range(1, t + 1):
        n, L = map(int, input().split())
        a, b, h = [], [], []
        for i in range(n):
            aa, bb, hh = map(int, input().split())
            a.append(aa)
            b.append(bb)
            h.append(hh)

        lo, hi = 0, min(h)
        while lo < hi:
            mid = (lo + hi + 1) >> 1
            if required(mid) <= L: lo = mid
            else: hi = mid - 1
        print(lo, L - required(lo))