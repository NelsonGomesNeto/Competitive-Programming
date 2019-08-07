import sys
sys.setrecursionlimit(2**20)
DEBUG = 0

def testRemove(string, target, remove, until):
    copy = string.copy()
    for i in remove[:until]:
        copy[i - 1] = 0
    if (DEBUG):
        print(copy, string)
    j = 0
    for i in copy:
        if (i == target[j]):
            j += 1
    if (j == len(target)):
        return(1)
    return(0)

def binSearch(string, target, remove, lo, hi):
    mid = lo + (hi - lo + 1) // 2
    if (lo >= hi):
        if (testRemove(string, target, remove, mid)):
            return(mid)
        return(mid + 1)
    #print("Removing from", mid, testRemove(string, target, remove, mid), lo, hi)
    if (testRemove(string, target, remove, mid)):
        return(binSearch(string, target, remove, mid, hi))
    return(binSearch(string, target, remove, lo, mid - 1))


string = list(input()) + ['\0']
target = list(input()) + ['\0']
remove = list(map(int, input().split()))
answer = binSearch(string, target, remove, 0, len(remove) - 1)
print(answer)