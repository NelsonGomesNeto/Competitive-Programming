while True:
    try:
        n = int(input())
    except EOFError:
        break
    a = list(map(int, input().split()))
    s = input()

    done = [False]*n
    memo = [0]*n
    path = ['\0']*n

    inf = 1e7
    def solve(i = 0):
        if i >= n - 1: return a[i] if i == n - 1 else 0
        if done[i]: return memo[i]

        ans = -inf
        for op in s:
            if (op == '+'):
                res = a[i] + solve(i + 1)
                if (res > ans):
                    ans = res
                    path[i] = op
            elif (op == '*'):
                res = a[i] * a[i + 1] + solve(i + 2)
                if (res > ans):
                    ans = res
                    path[i] = op
            else:
                res = a[i] - solve(i + 1)
                if (res > ans):
                    ans = res
                    path[i] = op
        done[i] = True
        memo[i] = ans
        return ans

    ans = solve()
    print(ans)
    res = ""
    i = 0
    while i < n:
        op = path[i]
        if (op == '*'):
            res += str(a[i]) + '*' + str(a[i + 1])
            i += 1
        else:
            if op != '\0':
                res += str(a[i]) + op
            else:
                res += str(a[i])
        i += 1
    print(res)