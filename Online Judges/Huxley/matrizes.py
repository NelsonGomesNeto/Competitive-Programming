def matriz():
  diagX = 0
  soma,t,a,b,c,d,x,y = 1,0,0,0,0,0,0,0
  matriz = [][]
  while True:
    n, m = map(int, input().split())
    if (n == 0 & m == 0):
        return(0)
    resultado = 0
    if (m > 0 & n > 0):
      diagyY, diagxY = n - 1,m - 1
      soma,diagX,t,a,b,c,d,x,y = 1,0,0,0,0,0,0,0,0
      j = 0
      while (j < n):
        i = 0
        while (i < m):
          t += soma
          matriz[i][j] = soma;
          soma += 1
          if (i == 0):
            a += matriz[i][j]
          if (i == m - 1):
            b += matriz[i][j]
          if (j == 0):
            c += matriz[i][j]
          if (j == n - 1):
            d += matriz[i][j]
          if (i == diagX & j == diagX):
            #printf("X: %d ~ %d %d\n", matriz[i][j], i, j);
            x += matriz[i][j]
            diagX += 1
          i += 1
        j += 1
    j = n - 1
    while (j >= 0):
        i = m - 1
        while (i >= 0):
            if (i == diagxY & j == diagyY):
                #printf("Y: %Ld ~ %d %d\n", matriz[i][j], i, j);
                y += matriz[i][j];
                diagyY -= 1; diagxY -= 1;
            i -= 1;
        if (n * m != 0 &  (t - (x + y) + (a * b) - (c * d)) != 0):
            resultado =  ((t - (x + y) + (a * b) - (c * d)) / (n * m));
        j -= 1
    print(resultado);
