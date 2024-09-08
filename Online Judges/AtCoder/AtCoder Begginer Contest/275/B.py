mod = 998244353
a, b, c, d, e, f = map(int, input().split())
print(((a * b * c) - (d * e * f)) % mod)