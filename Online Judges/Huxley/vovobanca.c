#include <stdio.h>

int main()
{
  int numerodias, saldoini, movimentodia, menorsaldo;
  scanf("%i %i\n%i", &numerodias, &saldoini, &movimentodia);
  saldoini += movimentodia;
  menorsaldo = saldoini;
  while (numerodias > 1)
  {
    scanf("%i", &movimentodia);
    saldoini += movimentodia;
    numerodias --;
    if (saldoini <= menorsaldo)
    {
      menorsaldo = saldoini;
    }
  }
  printf("%i\n", menorsaldo);
  return(0);
}
