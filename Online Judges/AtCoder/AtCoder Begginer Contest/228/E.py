mod = 998244353
n, k, m = map(int, input().split())
ans = pow(m, pow(k, n, mod - 1), mod)
if m % mod == 0:
    ans = 0
print(ans)