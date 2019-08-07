import sys
sys.setrecursionlimit(2**20)
DEBUG = 0

tests = int(input())
while (tests > 0):
    robbers, leftTime = map(int, input().split())
    robbersTime = list(map(int, input().split()))

    robbersTime.sort()
    maxSum = sum(robbersTime)
    subGroups = [0] * (maxSum + 1)
    subGroups[0] = 1
    if (DEBUG):
        print(robbersTime)
        print(maxSum)
    for r in robbersTime:
        theSum = maxSum
        while (theSum >= r):
            if (subGroups[theSum - r]):
                subGroups[theSum] = 1
            theSum -= 1

    times = []
    for i in range(maxSum + 1):
        if (subGroups[i]):
            times += [i]
    if (DEBUG):
        print("subGroups", subGroups)
        print("times", times)

    isValid = 0
    for i in range(max(0, maxSum - leftTime), leftTime + 1):
        if (i > maxSum):
            break
        if (subGroups[i]):
            isValid = 1

    if (isValid):
        print("YES")
    else:
        print("NO")

    tests -= 1
