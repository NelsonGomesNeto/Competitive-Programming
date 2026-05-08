from random import randint

n, m = int(1e3), int(1e3)
print(n, m)
for _ in range(n):
    s = ''.join([".#"[randint(0, 1)] for _ in range(m)])
    print(s)