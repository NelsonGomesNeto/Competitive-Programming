def binSearch(array, lo, hi, target):
    mid = lo + ((hi - lo) // 2)
    if (lo >= hi):
        if (array[mid] <= target):
            return(mid + 1)
        return(mid)
    if (array[mid] <= target):
        return(binSearch(array, mid + 1, hi, target))
    return(binSearch(array, lo, mid, target))

numShops = int(input())
shops = list(map(int, input().split()))
shops.sort()
days = int(input())
for i in range(days):
    spendable = int(input())
    boughtable = binSearch(shops, 0, numShops - 1, spendable)
    print(boughtable)