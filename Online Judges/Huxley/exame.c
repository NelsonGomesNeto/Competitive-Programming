#include <stdio.h>

int main()
{
  int D, P, U, N, grupo1, grupo2, soma;
  scanf("%d %d %d %d", &D, &P, &U, &N);
  grupo1 = (P - D);
  grupo2 = U - grupo1;
  soma = D + grupo1 + grupo2 + N;
  printf("%d\n", soma);
  return(0);
}
