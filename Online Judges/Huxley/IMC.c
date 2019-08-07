#include <stdio.h>

int main()
{
  float peso, altura, IMC;
  scanf("%f\n%f", &peso, &altura);
  IMC = peso / (altura * altura);
  if (IMC < 17)
  {
    printf("muito abaixo do peso\n");
  }
  else if (IMC < 18.5)
  {
    printf("abaixo do peso\n");
  }
  else if (IMC < 25)
  {
    printf("peso normal\n");
  }
  else if (IMC < 30)
  {
    printf("acima do peso\n");
  }
  else if (IMC < 35)
  {
    printf("obesidade\n");
  }
  else if (IMC < 40)
  {
    printf("obesidade severa\n");
  }
  else if (IMC >= 40)
  {
    printf("obesidade morbida\n");
  }
  return(0);
}
