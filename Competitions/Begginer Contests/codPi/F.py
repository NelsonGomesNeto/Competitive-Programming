tests = int(input())
while(tests > 0):
    size = int(input())
    array = list(map(int, input().split()))
    inc, dec = 1, 1
    for i in range(size):
        j = i + 1
        if (j < size):
            if (array[i] < array[j] and j + 1 < size and array[i] < array[j + 1]):
                dec = 0
    for i in range(size):
        j = i + 1
        if (j < size):
            if (array[i] > array[j] and j + 1 < size and array[i] > array[j + 1]):
                inc = 0

    if (inc == 1 or dec == 1):
        print("YES")
    else:
        print("NO")
    tests -= 1