global i

def getNum(treeString):
    global i
    num = 0
    while ('0' <= treeString[i] <= '9'):
        num = num * 10 + int(treeString[i])
        i += 1
    return(num)

def fillTree(treeString):
    global i
    if (i == len(treeString)): return([])
    if (treeString[i] == '('):
        i += 1
        if (treeString[i] == ')'):
            i += 1
            return([])
        else:
            num = getNum(treeString)
            t = [num]
            t += [fillTree(treeString)]
            t += [fillTree(treeString)]
            i += 1
            return(t)
    return([])

withSpacesTree = input()
treeString = ""
for s in withSpacesTree:
    if (s == ' '): continue
    treeString += s

i = 0
tree = fillTree(treeString)
print(tree)