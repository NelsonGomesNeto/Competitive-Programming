n = int(input())
ans = 2**n
s = []
while ans:
    s += [ans % 10]
    ans //= 10
s.reverse()
for i in range(len(s)):
    if (i % 50 == 0): print()
    print(s[i], end='')