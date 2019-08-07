inf = 2**33
DEBUG = 1

def solve(dp, cards, lo, hi):
    #print(lo, hi)
    if (lo >= hi):
        return(0)

    if (dp[lo][hi] == -1):
        aux = -inf
        me = cards[lo]
        #if (lo + 1 < len(cards)):
        if (cards[lo + 1] >= cards[hi]):
            greedy = cards[lo + 1]
            aux = max(aux, solve(dp, cards, lo + 2, hi) + (me - greedy))
        else:
            greedy = cards[hi]
            aux = max(aux, solve(dp, cards, lo + 1, hi - 1) + (me - greedy))
        me = cards[hi]
        #if (hi - 1 >= 0):
        if (cards[lo] >= cards[hi - 1]):
            greedy = cards[lo]
            aux = max(aux, solve(dp, cards, lo + 1, hi - 1) + (me - greedy))
        else:
            greedy = cards[hi - 1]
            aux = max(aux, solve(dp, cards, lo, hi - 2) + (me - greedy))
        dp[lo][hi] = aux

    return(dp[lo][hi])

run = 0
while (True):
    run += 1
    line = list(map(int, input().split()))
    qCards, cards = line[0], line[1:]
    if (qCards == 0):
        break
    dp = [[-1] * qCards for i in range(qCards)]
    answer = solve(dp, cards, 0, qCards - 1)
    #print(dp)
    print("In game ", run, ", the greedy strategy might lose by as many as ", answer, " points.", sep='')

