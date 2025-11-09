a = ['Direction::kUp','Direction::kRight','Direction::kDown','Direction::kLeft']

res = []
for i in range(len(a)):
    b = []
    for j in [-1, 1]:
        nxt = i + j
        if nxt < 0: nxt = 3
        if nxt > 3: nxt = 0
        b.append(a[nxt])
    res.append('{' + ','.join(b) + '}')
print(','.join(res))