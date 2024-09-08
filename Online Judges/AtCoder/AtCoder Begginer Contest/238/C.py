for n in range(1, 239):
    sum = 0
    for i in range(1, n + 1):
        aux = i
        while len(str(aux)) == len(str(i)) and aux > 0:
            sum += 1
            aux -= 1
    print(n, sum)