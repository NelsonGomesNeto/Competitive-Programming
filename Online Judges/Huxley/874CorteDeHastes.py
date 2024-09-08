import sys
sys.setrecursionlimit(2**20)
DEBUG = 0

def solve(dp, values, size):
    if (dp[size] == -1):
        for i in range(size):
            dp[size] = max(dp[size], values[i] + solve(dp, values, size - i - 1))
    return(dp[size])

while (True):
    size = int(input())
    if (size == 0):
        break

    dp = [-1] * (size + 1)
    dp[0] = 0

    values = []
    for i in range(size):
        values += [int(input())]
    if (DEBUG):
        print("values", values)
        
    answer = solve(dp, values, size)
    print(answer)