a = list(map(int, "45 33 17 60 28 9".split()))
ans = 0
n = len(a)
for i in range((n >> 1) + (n & 1)):
    b = a[i : -i]
    if i == 0:
        b = a
    print(b)
    for bb in b:
        ans ^= bb
print(ans)