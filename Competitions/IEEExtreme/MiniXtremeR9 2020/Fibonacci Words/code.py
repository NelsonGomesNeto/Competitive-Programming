q = int(input())
for t in range(q):
    a, b, n = input().split()
    n = int(n)

    wanted = n
    while wanted > 100000:
        fa, fb = len(a), len(b)
        while True:
            fb, fa = fa + fb, fb
            if fb > wanted:
                wanted = wanted - fa
                break
    if wanted <= len(a):
        print(a[wanted - 1])
        continue
    if wanted <= len(b):
        print(b[wanted - 1])
        continue
    while len(b) < wanted:
        b, a = a + b, b
    print(b[wanted - 1])