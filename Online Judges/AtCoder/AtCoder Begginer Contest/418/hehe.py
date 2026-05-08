def xnor(a, b):
    return 0 if a ^ b else 1

memo = {}
def brute(x):
    if len(x) == 1: return x[0] == 1
    if tuple(x) in memo: return memo[tuple(x)]
    for i in range(len(x) - 1):
        new_x = x[:i] + [xnor(x[i], x[i + 1])] + x[i + 2:]
        if brute(new_x):
            memo[tuple(x)] = True
            return True
    memo[tuple(x)] = False
    return False


for i in range(1, 100):
    x = list(map(int, bin(i)[2:]))
    cnt = {0: 0, 1: 0}
    for j in x:
        cnt[j] += 1
    res = x[0]
    for j in x[1:]:
        res = xnor(res, j)
    cor = brute(x)
    if (~cnt[0]&1) != cor:
        print(i, bin(i), "|", (cnt[0]&1), "|", res, "|", cor)

for i in range(1, 10):
    print(i, i * (i + 1) >> 1)