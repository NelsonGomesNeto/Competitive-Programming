def bob():
    dp = [[0 for j in range(m + 1)] for i in range(n + 1)]
    dp[0][1] = a[1][1]
    for i in range(1, n + 1):
        for j in range(1, m + 1):
            dp[i][j] = max(dp[i - 1][j] & a[i][j], dp[i][j - 1] & a[i][j])
    for i in range(n + 1):
        print(dp[i])
    return dp[n][m]

n, m = map(int, input().split())
a = [[]]
for i in range(n):
    a += [[0] + list(map(int, input().split()))]
print(bob())