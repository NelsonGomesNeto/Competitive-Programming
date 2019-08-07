inf = 2**33

def solve(dp, activities, i, end, done):
    if (i == end):
        return(0)

    if (dp[i][done] == -1):
        best = solve(dp, activities, i + 1, end, 0) + 1
        if ((activities[i] == 1 or activities[i] == 3) and done != 2):
            best = min(best, solve(dp, activities, i + 1, end, 2))
        if ((activities[i] == 2 or activities[i] == 3) and done != 1):
            best = min(best, solve(dp, activities, i + 1, end, 1))
        dp[i][done] = best

    return(dp[i][done])

days = int(input())
activities = list(map(int, input().split()))
dp = [[-1] * 4 for i in activities]
answer = solve(dp, activities, 0, days, 0)
#print(dp)
print(answer)





# 0 Nothing
# 1 Sports
# 2 Contest