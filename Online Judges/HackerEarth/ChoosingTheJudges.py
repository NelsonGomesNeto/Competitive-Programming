import sys
sys.setrecursionlimit(2**20)
tests = int(input())

def solve(dp, judge, i, end):
    if (i >= end):
        return(0)

    if (dp[i] == -1):
        dp[i] = solve(dp, judge, i + 1, end)
        dp[i] = max(dp[i], solve(dp, judge, i + 2, end) + judge[i])

    return(dp[i])

run = 0
while (tests > 0):
    run += 1
    judges = int(input())
    judge = list(map(int, input().split()))

    dp = [-1] * judges
    answer = solve(dp, judge, 0, judges)

    print("Case ", run, ": ", answer, sep='')
    tests -= 1