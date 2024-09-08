hehe = list(map(int, input().split()))
n, a = hehe[0], hehe[1:]
print(n, a)

for i in range(1, 20):
    print(a[1], i, a[1]*i, bin(a[1]*i), a[0] ^ a[1] ^ a[2])