size = int(input())
coins = list(map(int, input().split()))
coins.sort()
coins.reverse()
brother, needed, actual = sum(coins), 0, 0
for i in coins:
    if (actual > brother):
        break
    needed += 1
    actual += i
    brother -= i
print(needed)
