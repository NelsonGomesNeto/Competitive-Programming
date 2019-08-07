s = input()
end = len(s)
n = 0
for i in range(len(s)):
    n += (s[end - i - 1] == '1') << i

m = int(input())
ans = []
for i in range(m):
    a = int(input())
    if n % a == 0:
        ans += [a]

if len(ans) == 0:
    print("Nenhum")
else:
    ans.sort()
    print(*ans)