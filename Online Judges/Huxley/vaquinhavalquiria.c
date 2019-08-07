#include <stdio.h>

int main()
{
  float doar = 0, soma = 0, media = 0, divi = -1;
  while (doar >= 0 || divi == -1)
  {
    soma += doar;
    scanf("%f", &doar);
    divi ++;
  }
  if (soma != 0)
  {
    media = soma / (divi);
  }
  printf("%.2f\n%.2f\n", soma, media);
  return(0);
}
