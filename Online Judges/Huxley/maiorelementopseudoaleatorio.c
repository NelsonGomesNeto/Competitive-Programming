#include <stdio.h>
#include <math.h>

int biggest(int *num1, int num2)
{
  if (num2 > *num1)
  {
    *num1 = num2;
  }
}

int main()
{
  int A, B, C, seedX, seedY, seedZ, encher, soma;
  while (scanf("%d %d %d %d %d %d", &A, &B, &C, &seedX, &seedY, &seedZ) != EOF)
  {
    int X[10], Y[10], Z[10];
    X[0] = seedX; Y[0] = seedY; Z[0] = seedZ;
    int bigX = X[0], bigY = Y[0], bigZ = Z[0];
    for (encher = 1; encher < 10; encher ++)
    {
      X[encher] = (X[encher - 1] * B + C) % A;
      biggest(&bigX, X[encher]);
      Y[encher] = (Y[encher - 1] * A + B) % C;
      biggest(&bigY, Y[encher]);
      Z[encher] = (Z[encher - 1] * C + A) % B;
      biggest(&bigZ, Z[encher]);
    }
    soma = bigX + bigY + bigZ;
    soma %= ((A/B) + C);
    printf("%d\n", soma);
  }
  return(0);
}
