from math import sqrt, floor

def fix(num):
    while num > 1e9:
        num = num - num // 1000 * 1000
    return num
    # below = int(floor(num / 1000) * 1000)
    # return num - below

def pot(x, y):
    ans = 1
    while y:
        if y & 1:
            ans = ans * x
        x = x * x
        y >>= 1
        ans = fix(ans)
        x = fix(x)

    return ans

while True:
    try:
        a, b, n, k = list(map(int, input().split()))
    except EOFError:
        break

    # res = pow((a*1000 + int(sqrt(b)*1000)), n, 100000000000000000)
    # # lol = pow(a + sqrt(b), n)
    # lol = pot((a*1000 + int(sqrt(b)*1000)), n)
    res = pow(a**2 - b, n, 10000000)
    print(res)
