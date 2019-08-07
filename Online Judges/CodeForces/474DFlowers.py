mod = 10**9 + 7
fibonacci = [0] * (10**5 + 1)

def fillFib():
    a1, a2 = 0, 1
    for i in range(1, 10**5 + 1):
        fibonacci[i] = a1 + a2
        a1 = a2
        a2 = fibonacci[i]

fillFib()
tests, k = map(int, input().split())
ans, now = [0] * (10**5 + 1), 0
for i in range(1, 10**5 + 1):
    if (i < k):
        now += 1
    else:
        now += fibonacci[i - k + 2]
    ans[i] = now

while (tests > 0):
    a, b = map(int, input().split())
    print((ans[b] - ans[a - 1]) % mod)
    tests -= 1