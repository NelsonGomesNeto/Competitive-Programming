mod = int(1e9 + 7)

def inv(x):
    return pow(x, mod - 2, mod)

def gcd(a, b):
    return a if b == 0 else gcd(b, a % b)

def lcm(a, b):
    return a * b // gcd(a, b)

def mod_lcm(a, b):
    return a * b % mod * inv(gcd(a, b)) % mod


while True:
    try:
        n = int(input())
        a = list(map(int, input().split()))
    except:
        break

    l = a[0]
    for i in range(1, n):
        l = lcm(l, a[i])
    l %= mod

    ans = 0
    for i in range(n):
        ans = (ans + l * inv(a[i])) % mod
    print(ans)