#include <stdio.h>

int main()
{
  double saldo;
  printf("Informe o saldo inicial do cliente:\n");
  scanf("%lf", &saldo);
  double debitos;
  printf("Informe o total de debitos adquiridos pelo cliente:\n");
  scanf("%lf", &debitos);
  double creditos;
  printf("Informe o total de creditos adquiridos pelo cliente:\n");
  scanf("%lf", &creditos);
  saldo += creditos;
  saldo -= debitos;
  if (saldo > 0)
  {
    printf("Saldo positivo em R$ %.13lf\n", saldo);
  }
  else if (saldo < 0)
  {
    printf("Saldo negativo em R$ %.14lf\n", saldo);
  }
  else
  {
    printf("Saldo Zero\n");
  }
  return(0);
}
