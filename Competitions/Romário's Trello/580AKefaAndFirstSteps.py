size = int(input())
work = list(map(int, input().split()))
sequence, best, prev = 0, 0, work[0]
for i in work:
    if (i >= prev):
        sequence += 1
    else:
        sequence = 1
    best = max(best, sequence)
    prev = i
print(best)