#include <stdio.h>

int main()
{
  float largura, comprimento, altura;
  scanf("%f\n%f\n%f", &largura, &comprimento, &altura);
  if (largura <= 45 && comprimento <= 56 && altura <= 25)
  {
    printf("PERMITIDA\n");
  }
  else
  {
    printf("PROIBIDA\n");
  }
  return(0);
}
