DEBUG = 0

def solve(dp, wines, year, lo, hi):
    if (lo == hi):
        return(year * wines[lo])
    if (dp[lo][hi] == -1):
        dp[lo][hi] = max(dp[lo][hi], (wines[lo] * year) + solve(dp, wines, year + 1, lo + 1, hi), (wines[hi] * year) + solve(dp, wines, year + 1, lo, hi - 1))
    return(dp[lo][hi])

while (True):
    try:
        quantity = int(input())
        wines = [0] * (quantity + 1)
        for i in range(1, quantity + 1):
            wines[i] = int(input())
        if (DEBUG):
            print("wines", wines)

        dp = [[-1] * (quantity + 1) for i in range(quantity)]
        answer = solve(dp, wines, 1, 1, quantity)
        print(answer)
    except EOFError as e:
        break
