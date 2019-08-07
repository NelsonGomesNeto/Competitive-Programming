import sys
sys.setrecursionlimit(2**20)
inf = 2**33
DEBUG = 0

def solve(dp, sieve, problem, done, i, end):
    if (i == end):
        if (not sieve[done] and done != 0):
            return(-inf)
        return(0)
    if (dp[done][i] == -1):
        best, aux, aux2 = -inf, -inf, -inf
        aux = solve(dp, sieve, problem, done + 1, i + 1, end) + problem[i]
        #print("done", done)
        if (sieve[done] or done == 0):
            aux2 = solve(dp, sieve, problem, 0, i + 1, end)
        if (aux2 > aux):
            aux = aux2
        if (aux > best):
            best = aux
        dp[done][i] = best
    return(dp[done][i])

problems = int(input())
problem = list(map(int, input().split()))

sieve = [1] * (problems + 1)
sieve[0], sieve[1], sieve[2] = 0, 0, 1
for i in range(2, problems + 1):
    if (sieve[i]):
        for j in range(2, problems // i + 1):
            sieve[i*j] = 0
if (DEBUG == 2):
    for i, isPrime in enumerate(sieve):
        if (isPrime):
            print(i, end=' ')

dp = [[-1] * (problems + 1) for i in range(problems + 1)]
answer = solve(dp, sieve, problem, 0, 0, problems)
print(answer)