n = int(input())
a = list(map(int, input().split()))
a.sort()
while len(a) > 1:
  res = (a[0] + a[1]) / 2
  a = a[2:] + [res]
  a.sort()
print(a[0])