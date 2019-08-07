posts = int(input())
posts = map(int, input().split())
f, s = 0, 0
for i in posts:
    if (i < 50):
        s += 1
    if (i >= 50 and i < 85):
        f += 1

print(s, f)
