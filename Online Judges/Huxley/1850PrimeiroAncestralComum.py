DEBUG = 0

def search(tree, root, value, color, lowest):
    if (root == -1): return(lowest)
    color[root] += 1
    if (color[root] == 2): lowest = root
    if (tree[root][0] == value): return(lowest)
    if (value > tree[root][0]): return(search(tree, tree[root][2], value, color, lowest))
    else: return(search(tree, tree[root][1], value, color, lowest))
    return(lowest)

def addInBST(tree, root, i, u, prev):
    if (root == -1):
        tree[i] = [u, -1, -1]
        if (u > tree[prev][0]): tree[prev][2] = i
        else: tree[prev][1] = i
        return
    if (u > tree[root][0]): addInBST(tree, tree[root][2], i, u, root)
    else: addInBST(tree, tree[root][1], i, u, root)
    return

nodes = int(input())
nodesList = list(map(int, input().split()))
tree = [[] for i in range(nodes)]
tree[0] = [70, -1, -1]
for i, u in enumerate(nodesList[1:]):
    addInBST(tree, 0, i + 1, u, 0)
if (DEBUG): print("tree", tree)

while (True):
    try:
        query = list(map(int, input().split()))
    except:
        break
    color = [0] * nodes
    search(tree, 0, query[0], color, 0)
    ancestor = search(tree, 0, query[1], color, 0)
    print(tree[ancestor][0])