#include <stdio.h>
#include <math.h>

int main()
{
  double preco, parcelas[3], pmenor2, pmenor3;
  int dividido = 2;
  scanf("%lf", &preco);
  while (dividido >= 0)
  {
    parcelas[dividido] = preco / 3;
    dividido --;
  }
  pmenor2 = parcelas[1] - round(parcelas[1]);
  pmenor3 = parcelas[2] - round(parcelas[2]);
  parcelas[1] = round(parcelas[1]);
  parcelas[2] = round(parcelas[2]);
  parcelas[0] += (pmenor2) + (pmenor3);
  while (parcelas[1] > parcelas[0])
  {
    parcelas[0] ++;
    parcelas[0] ++;
    parcelas[1] --;
    parcelas[2] --;
  }
  dividido = 0;
  while (dividido < 3)
  {
    printf("%.2lf\n", parcelas[dividido]);
    dividido ++;
  }
  return(0);
}
