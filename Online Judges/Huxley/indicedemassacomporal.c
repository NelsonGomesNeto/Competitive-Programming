#include <stdio.h>

int main()
{
  float massa, altura, IMC;
  scanf("%f\n%f", &massa, &altura);
  IMC = (massa / (altura * altura));
  if (IMC < 18.5)
  {
    printf("%.2f MAGREZA\n", IMC);
  }
  else if (IMC < 24.5)
  {
    printf("%.2f SAUDAVEL\n", IMC);
  }
  else if (IMC < 30)
  {
    printf("%.2f SOBREPESO\n", IMC);
  }
  else
  {
    printf("%.2f OBESIDADE\n", IMC);
  }
  return(0);
}
