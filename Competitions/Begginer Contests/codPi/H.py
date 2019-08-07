tests = int(input())
while (tests > 0):
    size = int(input())
    func = list(map(int, input().split()))
    if (size == 2):
        print(func[0] * size)
    else:
        posMax, big = -1
        for i in range(size - 1):
            if (func[i] > big):
                big = func[i]
                posMax = i
        print(posMax, big)
        total, best = 0, func[0] * (size - 1) + func[1]
        for i in range(0, posMax):
            total += func[i]
            best = max(best, total + func[i] * (size - i - 1))
        total = func[]
    tests -= 1