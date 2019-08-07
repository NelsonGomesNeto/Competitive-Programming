#include <stdio.h>
#include <stdlib.h>

int main()
{
  int tam; scanf("%d", &tam);
  long long int A[tam], B[tam], C;
  long long int P, Q, R, S, X, Y;
  scanf("%Ld %Ld %Ld %Ld %Ld %Ld", &P, &Q, &R, &S, &X, &Y);
  int j, i;
  long long int x, y; scanf("%Ld %Ld", &x, &y);
  for (j = 0; j < tam; j ++)
  {
    A[j] = ((P * x) + (Q * (j + 1))) % X;
  }
  for (i = 0; i < tam; i ++)
  {
    B[i] = ((R * (i + 1)) + (S * (y))) % Y;
  }
  C = 0;
  int jM;
  for (i = 0; i < tam; i ++)
  {
    C += (A[i] * B[i]);
  }
  printf("%Ld\n", C);
  return(0);
}
