n = input()

ans = 0
for i in n:
  now = int(i)
  ans += min(now, 10 - now)

print(ans)