def valid():
    for i in range(len(now)):
        for j in range(i + 1, len(now)):
            if not now[i][2] and not now[j][2] and (now[i][0] == now[j][0] or now[i][1] == now[j][1]):
                return False
    return True

f = open("big", "r")
now, dest = [], []
n = int(f.readline())
for i in range(n):
    now += [list(map(int, f.readline().split()))]
    now[-1] += [False]
for i in range(n):
    dest += [list(map(int, f.readline().split()))]
f.close()

f = open("out", "r")
m = int(f.readline())
movements = []
for i in range(m):
    movements += [list(f.readline().split())]
    movements[-1] = int(movements[-1][0]), int(movements[-1][1]), movements[-1][2]
f.close()

dx = {'L': -1, 'R': 1, 'U': 0, 'D': 0}
dy = {'L': 0, 'R': 0, 'U': 1, 'D': -1}
# print(now)
# print(movements)
if m > 2050:
    print("Invalid!!", mov)
    exit(0)
for mov in movements:
    # print(mov, now)
    for i in range(n):
        if (now[i][0] == mov[0] and now[i][1] == mov[1]):
            if mov[2] == 'T':
                now[i][2] = True
            elif mov[2] == 'P':
                now[i][2] = False
            else:
                now[i][0] += dx[mov[2]]
                now[i][1] += dy[mov[2]]
            break
    if not valid():
        print("Invalid!!", mov)
        exit(0)
print("Valid!")