while (True):
    q = list(map(float, input().split()))
    if (q[0] == 0):
        break
    q, d, p = q[0], q[1], q[2]
    x2 = d / (1.0 - (q / p))
    pages = x2 * q
    if (int(pages) == 1):
        print("1 pagina")
    else:
        print(int(pages), "paginas")