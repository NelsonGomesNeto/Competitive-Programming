def formula(p, t):
  return(0.8 * p + 0.2 * t)

feedSize = int(input())
friends = int(input())

proximity = {}
for i in range(friends):
  id, p = input().split()
  id, p = int(id), float(p)
  proximity[id] = p

updates = int(input())
update = []
for i in range(updates):
  line = list(input().split(' '))
  id, t, s = int(line[0]), float(line[1]), " ".join(line[2:])
  update += [[formula(proximity[id], t), id, s]]
update.sort()
#print(update)

for i in range(feedSize):
  new = str(update[updates - i - 1][1]) + " " + update[updates - i - 1][2]
  print(new)