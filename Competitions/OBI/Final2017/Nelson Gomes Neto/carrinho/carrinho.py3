s = input().split()
bat, track = int(s[0]), float(s[1])
#print(bat, track)
b = [0] * (bat + 1)
prev = 0
for i in range(bat):
    b[i] = list(map(float, input().split()))
    if (i > 0):
        d = (b[i][0] - prev)
        #print(d / (b[i - 1][1] / d))
    prev = b[i][0]

b[bat] = [track, 0]
#print(b)

t, i = 0, 0
while (i < bat):
    j = 2
    prev = (b[i + 1][0] - b[i][0])**2 / b[i][1]
    #print((b[i + j][0] - b[i][0])**2 / b[i][1], (b[i + j][0] - b[i + j - 1][0])**2 / b[i + j - 1][1])
    while (i + j <= bat and (b[i + j][0] - b[i][0])**2 / b[i][1] <= (b[i + j][0] - b[i + j - 1][0])**2 / b[i + j - 1][1] + 0):
        prev = (b[i + j][0] - b[i][0])**2 / b[i][1]
        j += 1
    t += prev
    #print(t, j)
    i += j - 1

print("%.3lf" % t)
# d² / C
# check if that "+ 0" should be a "+ prev" or not
