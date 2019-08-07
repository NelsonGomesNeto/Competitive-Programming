def binSearch(array, lo, hi, target):
    mid = (lo + hi) // 2
    if (lo >= hi):
        if (array[mid] == target):
            return(mid)
        return(-1)
    if (array[mid] >= target):
        return(binSearch(array, lo, mid, target))
    return(binSearch(array, mid + 1, hi, target))

case = 0
while (True):
    case += 1
    numMarble, queries = map(int, input().split())
    if (numMarble == 0 and queries == 0):
        break

    marble = []
    for i in range(numMarble):
        marble += [int(input())]
    marble.sort()

    print("CASE# %d:" % case)
    for i in range(queries):
        q = int(input())
        pos = binSearch(marble, 0, numMarble - 1, q)
        if (pos == -1):
            print(q, "not found")
        else:
            print(q, "found at", pos + 1)