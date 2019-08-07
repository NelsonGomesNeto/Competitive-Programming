from heapq import *
DEBUG = 0

def inOrderPrint(tree):
  if (tree == None): return
  inOrderPrint(tree[2])
  print(tree[1], end='')
  inOrderPrint(tree[3])

def decode(tree, now, decoded):
  if (tree == None): return
  if (tree[1] != '*'):
    decoded[ord(tree[1])] = now
  left = decode(tree[2], now + "0", decoded)
  right = decode(tree[3], now + "1", decoded)

string = input()
frequency = [0] * 256
for s in string:
  frequency[ord(s)] += 1
if (DEBUG): print(frequency)

pq = []
for i in range(256):
  if (frequency[i] == 0):
    continue
  heappush(pq, [frequency[i], [i, chr(i), None, None]])
if (DEBUG): print(pq)

while (len(pq) > 1):
  a = heappop(pq)
  b = heappop(pq)
  aF, aT = a
  bF, bT = b
  heappush(pq, [aF + bF, [ord('*'), '*', aT, bT]])
  if (DEBUG): print(pq)
huffTree = heappop(pq)[1]
if (DEBUG): print(huffTree)

print("Tree\t-\t", end='')
inOrderPrint(huffTree)
print()

decoded = [""] * 256
decode(huffTree, "", decoded)
for i in range(256):
  if (frequency[i] == 0): continue
  print("%c\t-\t%s" % (chr(i), decoded[i]))
