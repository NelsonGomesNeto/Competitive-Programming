#include <stdio.h>

int somadosdivi;

int divisores(int numero, int divi)
{
  if (numero == divi)
  {
    somadosdivi = 0;
  }
  if (numero % divi == 0)
  {
    somadosdivi += divi;
  }
  if (divi != 1)
  {
    divisores(numero,divi - 1);
  }
  return(somadosdivi);
}

int main()
{
  int num[5], soma[5], ler, ordem, aux;
  for (ler = 0; ler < 5; ler ++)
  {
    scanf("%d", &num[ler]);
    soma[ler] = divisores(num[ler], num[ler]);
  }
  for (ler = 0; ler < 5; ler ++)
  {
    for (ordem = 0; ordem < 5; ordem ++)
    {
      if (soma[ler] > soma[ordem])
      {
        aux = soma[ler];
        soma[ler] = soma[ordem];
        soma[ordem] = aux;
        aux = num[ler];
        num[ler] = num[ordem];
        num[ordem] = aux;
      }
    }
  }
  printf("%d\n", num[0]);
  return(0);
}
