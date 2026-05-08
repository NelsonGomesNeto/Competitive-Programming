for n in range(1, 100):
    ans = 0
    for i in range(n):
        for j in range(i, n):
            to_add = j - i + 1
            ans += to_add
    ans2 = (n + 2) * (n + 1) // 2 * n // 3
    print(n, ans, ans2)
    assert ans == ans2