n, l, r = map(int, input().split())
box = []
for i in range(n):
    box += [list(map(int, input().split()))]

total = 0
for i in range(n):
    firstX = box[i][0] + box[i][1]
    lastX = box[i][2] + box[i][3]
    fx, lx = max(firstX, l), min(lastX, r)

    uly = min(lx - box[i][2], box[i][3])
    dly = max(box[i][3]+(lx - box[i][2]), box[i][1])

    ufy = max(box[i][0] - fx, box[i][3])
    dfy = min(-(box[i][0] - fx), box[i][1])

    print(uly, dly, ufy, dfy)
    print(box[i][1], box[i][3])

    total += (lx - fx) * (box[i][2] - box[i][0])
print(total)

# uly = min(lx - box[i][2], box[i][3])
# dly = max(-(lx - box[i][2]), box[i][1])

# ufy = max(box[i][0] - fx, box[i][3])
# dfy = min(-(box[i][0] - fx), box[i][1])

# uly = (lx - box[i][2])
# dly = -(lx - box[i][2])
#
# ufy = (box[i][0] - fx)
# dfy = -(box[i][0] - fx)