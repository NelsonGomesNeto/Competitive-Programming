import sys

def solve():
    memo = [[0 for _ in range(10)] for _ in range(n + 1)]

    ans = []
    for target in range(10):
        for d in range(10):
            memo[n][d] = -int(1e18)*(d != target)

        for i in range(n - 1, -1, -1):
            for d in range(10):
                # new_d = (d + aa[i]) % 10
                # new_d = aad[i][d]
                notPut, put = memo[i + 1][d], memo[i + 1][aad[i][d]] + a[i]
                memo[i][d] = put if put > notPut else notPut
        ans.append(max(memo[0][0], -1))

    return ans

while True:
    try:
        n = int(input())
    except EOFError:
        break

    a = list(map(int, input().split()))
    aa = list(map(lambda x: x % 10, a))
    aad = []
    for aai in aa:
        aad.append([(d + aai) % 10 for d in range(10)])

    ans = solve()
    print(*ans)