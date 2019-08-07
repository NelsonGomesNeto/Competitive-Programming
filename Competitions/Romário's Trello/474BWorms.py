def binSearch(array, lo, hi, target):
    mid = (lo + hi) // 2
    if (lo >= hi):
        return(mid // 2)
    if (array[mid] >= target):
        return(binSearch(array, lo, mid, target))
    return(binSearch(array, mid + 1, hi, target))

numPiles = int(input())
piles = list(map(int, input().split()))
worms, prev = [], 0
for i, j in enumerate(piles):
    worms += [prev + 1]
    worms += [prev + j]
    prev += j
numQueries = int(input())
queries = list(map(int, input().split()))
for i in queries:
    print(binSearch(worms, 0, numPiles * 2, i) + 1)