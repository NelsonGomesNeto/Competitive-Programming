#include <stdio.h>
#include <math.h>

int repeat;

float mediaF(float n[], int tam)
{
  int soma = 0;
  for (repeat = 0; repeat < tam; repeat ++)
  {
    soma  += n[repeat];
  }
  return((float) soma/tam);
}
float varianciaF(float n[], int tam)
{
  float media = mediaF(n, tam), variancia = 0;
  for (repeat = 0; repeat < tam; repeat ++)
  {
    if (media >= n[repeat])
    {
      variancia += (float) pow((media - n[repeat]), 2) / tam;
    }
    else
    {
      variancia += (float) pow((n[repeat] - media), 2) / tam;
    }
  }
  return(variancia);
}
float desvio_padraoF(float n[], int tam)
{
  float desvio = varianciaF(n, tam);
  return(sqrt(desvio));
}

int main()
{
  int taman; scanf("%i", &taman);
  float num[taman], media = 0, desvio = 0;
  for (repeat = 0; repeat < taman; repeat ++)
  {
    scanf("%f", &num[repeat]);
    //media += num[repeat] / n;
  }
  //media = mediaF(num[], n);
  /*for (repeat = 0; repeat < n; repeat ++)
  {
    if (media >= num[repeat])
    {
      desvio += pow((media - num[repeat]), 2) / n;
    }
    else
    {
      desvio += pow((num[repeat] - media), 2) / n;
    }
  }*/
  desvio = desvio_padraoF(num, taman);
  //sqrt(desvio);
  printf("%.2f\n", desvio);
  return(0);
}
