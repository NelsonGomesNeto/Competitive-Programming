while True:
    try:
        n, k = map(int, input().split())
    except EOFError:
        break

    i = 0
    while i < k:
        while n % 200 == 0 and i < k:
            n //= 200
            i += 1
        if i < k:
            n = int(str(n) + "200")
            i += 1
        # print('\t', n)
    print(n)