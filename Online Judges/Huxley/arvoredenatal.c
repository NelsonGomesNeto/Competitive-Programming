#include <stdio.h>

int main()
{
  float arvore, preco = 0;
  int quantidade[3], vetor;
  float enfeite[3];
  scanf("%f\n", &arvore);
  preco += arvore;
  for (vetor = 0; vetor < 3; vetor++)
  {
    scanf("%i\n%f", &quantidade[vetor], &enfeite[vetor]);
    preco += quantidade[vetor] * enfeite[vetor];
  }
  printf("%.2f\n%.2f\n", preco, preco / 21);
  return(0);
}
