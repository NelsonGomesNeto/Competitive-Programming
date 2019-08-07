def binPack(s, i, now, target, dp):
    if (i == len(s)): return(now == target)

    if (dp[i][now] == -1):
        a1 = binPack(s, i + 1, abs(now - s[i]), target, dp)
        a2 = binPack(s, i + 1, abs(now + s[i]), target, dp)
        dp[i][now] = (a1 or a2)

    return(dp[i][now])

s = list(map(int, input().split()))
target = int(input())

dp = [[-1] * (sum(s) + 1) for i in range(len(s))]
ans = binPack(s, 0, 0, target, dp)

if (ans):
    print("Yes")
else:
    print("No")