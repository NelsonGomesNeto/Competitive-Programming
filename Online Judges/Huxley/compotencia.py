def compotencia():
    while True:
        try:
            repeat = 1
            N1, N2 = map(int, input().split())
            resto1 = N1 % 100
            resto2 = N2 % 100
            while (repeat < N1):
                resto1 = (resto1 * N1) % 100
                repeat += 1
            repeat = 1
            #resto1 = (resto1 ** N1) % 100
            #resto2 = (resto2 ** N2) % 100
            while (repeat < N2):
                resto2 = (resto2 * N2) % 100
                repeat += 1
            resto1 = resto1 % 100
            resto2 = resto2 % 100
            if (resto1 > resto2):
                print(N1)
            else:
                if (resto2 > resto1):
                    print(N2)
                else:
                    print("0")
        except EOFError:
            break


compotencia()
