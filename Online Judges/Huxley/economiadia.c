#include <stdio.h>

int main()
{
  int semana = 7, meta = 0;
  float valor = 9999, valorontem, soma = 0;
  while (semana > 0)
  {
    valorontem = valor;
    scanf("%f", &valor);
    if (valor - valorontem >= 0.5)
    {
      meta ++;
    }
    soma += valor;
    semana --;
  }
  printf("R$ %.2f\n%i\n", soma, meta);
  return(0);
}
