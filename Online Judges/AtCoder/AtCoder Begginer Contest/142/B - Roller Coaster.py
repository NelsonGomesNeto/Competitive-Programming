n, minh = list(map(int, input().split()))
h = list(map(int, input().split()))
ans = 0
for i in h:
  if (i >= minh):
    ans += 1
print(ans)
