def check(p, a):
    t = 0
    for i in p[0:a]:
        t += i
    return(t)

def change(f, a, n, changed):
    for i in range(a, len(f)):
        f[i] -= changed

floors, events = map(int, input().split())
p = list(map(int, input().split()))
f = [0] * floors
j, prev = 0, 0
for i in p:
    f[j] = i + prev
    prev = f[j]
    j += 1

for i in range(events):
    e = list(map(int, input().split()))
    if (e[0] == 0): # mudança
        change(f, e[1] - 1, e[2], p[e[1] - 1] - e[2])
        p[e[1] - 1] = e[2]
    else: # bombeiro
        print(f[e[1] - 1])
