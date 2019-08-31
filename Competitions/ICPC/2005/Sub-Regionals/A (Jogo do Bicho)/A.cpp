#include <stdio.h>
#include <math.h>

long long int milhar(long long int num)
{
  return((num % 10000) / 1000);
}
long long int centena(long long int num)
{
  return((num % 1000) / 100);
}
long long int dezena(long long int num)
{
  return((num % 100) / 10);
}
long long int unidade(long long int num)
{
  return(num % 10);
}
int main()
{
  long double valor; long long int aposta, sorte;
  while (scanf("%Lf %Ld %Ld", &valor, &aposta, &sorte) && !(valor == 0 && aposta == 0 && sorte == 0))
  {
    if (milhar(aposta) == milhar(sorte) && centena(aposta) == centena(sorte) && dezena(aposta) == dezena(sorte) && unidade(aposta) == unidade(sorte))
    {
      printf("%.2LF\n", valor * 3000);
    }
    else if (centena(aposta) == centena(sorte) && dezena(aposta) == dezena(sorte) && unidade(aposta) == unidade(sorte))
    {
      printf("%.2Lf\n", valor * 500);
    }
    else if (dezena(aposta) == dezena(sorte) && unidade(aposta) == unidade(sorte))
    {
      printf("%.2Lf\n", valor * 50);
    }
    else if (ceil((long double)(aposta % 100) / 4) == ceil((long double)(sorte % 100) / 4) || ((sorte % 100) == 0 && (aposta % 100) > 96))
    {
      printf("%.2Lf\n", valor * 16);
    }
    else
    {
      printf("%.2Lf\n", (long double)0);
    }
  }
  return(0);
}
