def binSearch(array, lo, hi, target):
    mid = lo + (hi - lo) // 2
    if (lo >= hi):
        if (array[mid] <= target):
            return(mid)
        return(mid - 1)
    if (array[mid] <= target):
        return(binSearch(array, mid + 1, hi, target))
    return(binSearch(array, lo, mid, target))

potions, first, second = map(int, input().split())
preparationTime, mana = map(int, input().split())
first = list(map(int, input().split()))
manaFirst = list(map(int, input().split()))
second = list(map(int, input().split()))
manaSecond = list(map(int, input().split()))

time = preparationTime * potions
# Buying best lv 2 magic without any lv 1 magic
buyThis = binSearch(manaSecond, 0, len(second) - 1, mana)
if (buyThis != -1):
    time = min(time, preparationTime * (potions - second[buyThis]))
# Choosing best lv 2 magic for each lv 1 magic
for i in range(len(first)):
    magic, cost = first[i], manaFirst[i]
    if (cost <= mana):
        buyThis = binSearch(manaSecond, 0, len(second) - 1, mana - cost)
        if (buyThis == -1):
            time = min(time, magic * potions)
        else:
            time = min(time, magic * (potions - second[buyThis]))

print(time)