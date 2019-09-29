n = int(input())
even, odd = n >> 1, (n >> 1) + (n & 1)
print(odd / n)
