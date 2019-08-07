import sys
inf = 2**33
sys.setrecursionlimit(2**20)

def solve(dp, wa, original, smallest):
    if (original >= 0 and dp[original] != -1):
        return(dp[original])
    if (original - smallest < 0):
        return(-inf)

    cuts = -inf
    for i in wa:
        cuts = max(cuts, solve(dp, wa, original - i, smallest) + 1)
    dp[original] = cuts

    return(dp[original])

original, a, b, c = map(int, input().split())
wanted = [a, b, c]
smallest = min(wanted)
dp = [-1] * (original + 1)
dp[0] = 0
solve(dp, wanted, original, smallest)
print(dp[original])