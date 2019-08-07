import sys
sys.setrecursionlimit(2**20)

def solve(dp, robbersTime, actual, i, leftTime):
    if (i == len(robbersTime)):
        return(0)

    if (dp[i][actual] == -1):
        best, aux = solve(dp, robbersTime, actual, i + 1, leftTime), 0
        if (actual + robbersTime[i] <= leftTime):
            aux = solve(dp, robbersTime, actual + robbersTime[i], i + 1, leftTime) + robbersTime[i]
        dp[i][actual] = best if (best > aux) else aux

    return(dp[i][actual])

tests = int(input())
while (tests > 0):
    robbers, leftTime = map(int, input().split())
    robbersTime = list(map(int, input().split()))

    dp = [[-1] * (leftTime + 1) for i in range(robbers + 1)]
    answer = solve(dp, robbersTime, 0, 0, leftTime)

    everyRobber = sum(robbersTime)
    #print(answer, everyRobber)
    if (everyRobber - answer > leftTime):
        print("NO")
    else:
        print("YES")

    tests -= 1