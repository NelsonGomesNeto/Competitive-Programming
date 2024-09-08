a = [1]*5
global it
it = 0

def dfs(i: int = 0):
    global it
    if it > 27:
        return
    if i == 4:
        print(it, "-", *a)
        it += 1
        return
    for j in range(5):
        dfs(i + 1)
        a[i] = a[i] % 5 + 1

dfs()