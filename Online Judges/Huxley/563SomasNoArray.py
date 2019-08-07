tests, run = int(input()), 0
while (run < tests):
    coins, queries = map(int, input().split())
    coin = list(map(int, input().split()))

    biggest = 100000
    coinChange = [[0] * (biggest + 1) for i in range(coins + 1)]
    for i in range(coins + 1):
        coinChange[i][0] = 1
    for i in range(biggest + 1)[1:]:
        coinChange[0][i] = 0

    for i in range(coins + 1)[1:]:
        for fill in range(biggest + 1):
            if (fill < coin[i - 1]):
                coinChange[i][fill] = coinChange[i - 1][fill]
            else:
                coinChange[i][fill] = coinChange[i - 1][fill] or coinChange[i - 1][fill - coin[i - 1]]
    run += 1
    print("caso ", run, ":", sep='')
    for i in range(queries):
        elements, sumTarget = map(int, input().split())
        print(coinChange[elements][sumTarget], end=' ')
    print("\b")
