size = int(input())
array = []
for i in range(size):
    array += [int(input())]

setted = set(array)
if (len(setted) % 2 == 0):
    ans, odd = [], 0
    for i in setted:
        if (array.count(i) % 2 != 0):
            odd += 1
        #print(array.count(i), odd)
        ans += [i]
    if (odd % 2 != 0 or odd == 0):
        print("YES")
        for i in ans:
            print(i, end=' ')
    else:
        print("NO")
        #print(i, end=' ')
else:
    print("NO")