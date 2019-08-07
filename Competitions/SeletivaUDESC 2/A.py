import sys
sys.setrecursionlimit(2**20)
mod = int(1e9 + 9)
dx = [2, 2, -2, -2, 1, -1, 1, -1]
dy = [1, -1, 1, -1, 2, 2, -2, -2]

def pot(x, n):
    if (n == 0): return(1)
    ret = pot(x, n // 2)
    ret = (ret * ret) % mod
    if (n & 1): ret = (ret * x) % mod
    return(ret)

t = int(input())
for r in range(t):
    n, m = map(int, input().split())
    if (n > m): n, m = m, n
    base = 2**(n*m)#pot(2, n*m)
    bug, bug1, bug2 = 0, 0, 0
    if (n >= 2 and m >= 3):
        for i in range(n - 1):
            for j in range(m - 2):
                bug1 = (bug1 + 2) % mod
        lol1 = 2**(bug1) - 1
        for i in range(m - 1):
            for j in range(n - 2):
                bug2 = (bug2 + 2) % mod
        lol2 = 2**(bug2) - 1
        bug = (2**(bug1+bug2)-1)#(lol1 + lol2) % mod
    answer = (base - (bug)) % mod
    print(answer)