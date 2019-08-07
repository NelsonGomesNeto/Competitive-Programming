import sys
sys.setrecursionlimit(2**20)
dx = [1, 5, 10, 20, 50, 100, 200, 500, 1000, 2000]
inf = 2**33

def solve(dp, amount, original, smallest):
    if (original >= 0 and dp[original] != -1):
        return(dp[original])
    if (original - smallest < 0 or original < 0):
        return(-inf)

    cuts = -inf
    for i in range(len(amount)):
        if (amount[i] > 0):
            amount[i] -= 1
            cuts = max(cuts, solve(dp, amount, original - dx[i], smallest) + 1)
            amount[i] += 1
    dp[original] = cuts

    return(dp[original])

tests = int(input())
while (tests > 0):
    line = list(map(int, input().split()))
    buy, amount = line[0], line[1:]
    dp = [-1] * (buy + 1)
    dp[0] = 0
    smallest = 0
    print(line, buy, amount)
    for i in range(len(amount)):
        if (amount[i] > 0):
            smallest = dx[i]
            break
    solve(dp, amount, buy, smallest)
    if (dp[buy] < -inf + 1000000):
        print(-1)
    else:
        print(dp[buy])
    tests -= 1