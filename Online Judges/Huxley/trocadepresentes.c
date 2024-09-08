#include <stdio.h>

int main()
{
  float present, din = 0; int quant, repeat, troca = 0;
  for (repeat = 0; repeat < 6; repeat ++)
  {
    scanf("%f\n%i", &present, &quant);
    if (quant > 1 && din < 800)
    {
      troca += (quant - 1);
      din += present * (quant - 1);
    }
  }
  if (din >= 800)
  {
    printf("%i\nSIM\n", troca);
  }
  else { printf("%i\nNAO\n", troca); }
  return(0);
}
