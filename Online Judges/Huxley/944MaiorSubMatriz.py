DEBUG = 1

def printMatrix(mat):
    for i in mat:
        for j in i:
            print(j, end=' ')
        print()

def solve(mat, iLo, jLo, iHi, jHi, target):

    best = 0
    if ((target == -1 and mat[iLo][jLo] == mat[iHi][jHi]) or (target == mat[iLo][jLo] and target == mat[iHi][jHi])):
        best = solve(mat, iLo + 1, jLo + 1, iHi - 1, jHi - 1) + ()


    return(best)

tests = int(input())
while (tests > 0):
    trash = input()

    line = list(input())
    dim = len(line) - 1
    line.pop(dim)
    mat = [[] for i in line]
    mat[0] += line
    for i in range(dim - 1):
        newLine = list(input())
        if (len(newLine) > dim):
            newLine.pop(dim)
        mat[i + 1] += newLine
    if (DEBUG):
        print("mat")
        printMatrix(mat)

    answer = solve(mat, 0, 0, len(line) - 1, len(line) - 1, -1)

    tests -= 1