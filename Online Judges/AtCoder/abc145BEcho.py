n = int(input())
s = input()
if n & 1:
  print("No")
else:
  can = True
  for i in range(n >> 1):
    if s[i] != s[i + (n >> 1)]:
      can = False
  if can:
    print("Yes")
  else:
    print("No")
