mod = 10**9 + 7

def pot(x, n):
    return(x**n)
    if (n == 0): return(1)
    if (n == 1): return(x)
    if (n % 2 != 0):
        half = pot(x, (n - 1) // 2)
        return((half * half * x))
    else:
        half = pot(x, n // 2)
        return((half * half))

def pgSum(a1, r, n):
    return(a1*(pot(r, n) - 1) // (r - 1))

s = str(input())
k = int(input())
at = [0] * len(s)
for i in range(len(s)):
    if (s[i] == '0' or s[i] == '5'):
        at[i] = 1

total = 0
for i in range(len(s)):
    a1, r = pot(2, i), pot(2, len(s))
    if (at[i]):
        print(a1 % mod, r % mod, pgSum(a1, r, k) % mod, pot(r, k) % mod, (a1*pot(r, k)) % mod)
        total = (total + pgSum(a1 % mod, r % mod, k % mod)) % mod

print(total % mod)