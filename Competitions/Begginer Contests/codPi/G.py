from math import atan2, atan, degrees, sqrt

def norm(p1, p2):
    return(sqrt((p2[1] - p1[1])**2 + (p2[0] - p1[0])**2))
def ang(p1, p2):
    return(abs(atan2(p2[1] - p1[1], p2[0] - p1[0])))

tests = int(input())
while (tests > 0):
    #print()
    size = int(input())
    coordinates = []
    for i in range(size):
        coordinates += [list(map(int, input().split()))]
    #print(coordinates)
    mostAppearing, isColinear = {}, 0
    for i in range(size):
        colinear = {}
        for j in range(size):
            if (i != j):
                theAngle = ang(coordinates[i], coordinates[j])
                if (theAngle not in mostAppearing):
                    mostAppearing[theAngle] = [0, theAngle, norm(coordinates[0], coordinates[1])]
                mostAppearing[theAngle][0] += 1
                if (theAngle not in colinear):
                    colinear[theAngle] = 0
                else:
                    isColinear = 1
                    break
    if (isColinear == 1):
        #print("Colinear")
        print("NO")
    else:
        done = [0] * size
        appeared, bestAngle, bestDistance = 0, 180, 0
        for i in mostAppearing:
            if mostAppearing[i][0] > appeared:
                bestAngle, bestDistance = mostAppearing[i][1:]
                appeared = mostAppearing[i][0]
        regular = 0
        deg = degrees(bestAngle)
        #print("selected", degrees(bestAngle), bestDistance)
        if (deg != 180):
            for p in range(size):
                regular = 0
                if (done[p] < 4):
                    for i in range(size):
                        if (done[i] < 4):
                            if (bestAngle == ang(coordinates[p], coordinates[i]) and bestDistance == norm(coordinates[p], coordinates[i])):
                                #print("Wee", p, i)
                                done[i] += 1
                                done[p] += 1
                                regular = 1
                                break
                if (regular == 0):
                    break
        #print(colinear)
        if (regular == 1):
            print("YES")
        else:
            print("NO")
    tests -= 1