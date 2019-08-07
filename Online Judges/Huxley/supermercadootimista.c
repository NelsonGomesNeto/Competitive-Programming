#include <stdio.h>
#include <string.h>
#include <math.h>

int main()
{
  char dia[1000], opcao[1000], nome[1000];
  long double preco;
  scanf("%s\n%Lf\n%s\n%s", dia, &preco, opcao, nome);

  if (strcmp(opcao, "ouro") == 0 && (strcmp(dia, "seg") == 0 || strcmp(dia, "ter") == 0 || strcmp(dia, "qua") == 0))
  {
    preco /= 2;
  }
  else if ((strcmp(dia, "qui") == 0 || strcmp(dia, "sex") == 0) && preco > 10 && preco < 100)
  {
    preco /= 3;
  }
  else if (strcmp(opcao, "prata") == 0 && strcmp(dia, "sab"))
  {
    preco *= 3;
  }
  else
  {
    preco *= 2;
  }

  if ((int) (preco * 10) == (long double) (preco * 10))
  {
    printf("O preco do produto %s no dia %s eh %.1lf\n", nome, dia, round(preco * 100) / 100);
  }
  else
  {
    printf("O preco do produto %s no dia %s eh %.2lf\n", nome, dia, round(preco * 100) / 100);
  }

  return(0);
}
