#include <stdio.h>

long double fat(long double num)
{
  if (num == 0)
  {
    return(1);
  }
  else
  {
    num *= fat(num - 1);
  }
  return(num);
}

void SomaTermos(long double numero, long double *soma)
{
  long double divi = 0;
  while (numero > 0)
  {
    *soma += numero/fat(divi);
    divi ++; numero --;
  }
}

int main()
{
  long double n;
  while (scanf("%Lf", &n) != EOF)
  {
    long double soma  = 0;
    SomaTermos(n, &soma);
    printf("%Lf\n", soma);
  }
  return(0);
}
