#include <stdio.h>

int main()
{
  int n, M, C, D, U, n1;
  scanf("%i", &n);
  U = (((n % 1000) % 100) % 10); //Pega unidade de n
  D = (n % 100) / 10; //Pega dezena de n
  C = (n / 100) % 10; //Pega centena de n
  M = n / 1000; //Pega milhar de n
  n1 = (U * 1000) + (D * 100) + (C * 10) + M; //Joga tudo invertido para n1
  printf("%i\n", n1);
  return(0);
}
