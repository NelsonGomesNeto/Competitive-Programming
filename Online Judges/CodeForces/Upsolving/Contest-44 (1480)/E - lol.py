import sys
sys.setrecursionlimit(2**30)

memo = [-1] * 40
def hehe(base, left):
    if left == 0:
        return 1
    if memo[left] != -1:
        return memo[left]

    ans = max(i * base * hehe(base, left - i) for i in range(1, left + 1))
    memo[left] = ans
    return ans

while True:
    base = int(input())
    print(hehe(base, base))