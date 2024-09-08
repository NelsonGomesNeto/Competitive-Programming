from math import factorial

fat = factorial
mod = int(1e9) + 7

p = 1
for i in range(1, 20):
    p = p * fat(i) % mod
    print(i, fat(i) % mod)