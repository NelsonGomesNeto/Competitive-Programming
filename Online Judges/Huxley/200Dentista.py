size = int(input())

consultation = []
for i in range(size):
    line = list(map(int, input().split()))
    line.reverse()
    consultation += [line]
consultation.sort()

firstToEnd, canHappen = consultation[0][0], 1
for i in consultation:
    end, begin = i
    if (begin >= firstToEnd):
        canHappen += 1
        firstToEnd = end

print(canHappen)
