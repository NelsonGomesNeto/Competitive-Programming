#include <stdio.h>

int exercio(int n)
{
  int resultado;
  if (n > 1)
  {
    resultado = 1 + exercio(n - 2);
  }
  else
  {
    if (n == 0)
    {
      resultado = 3;
    }
    else
    {
      resultado = 2;
    }
  }
  return(resultado);
}

int main()
{
  int num;
  while (scanf("%d", &num) != EOF)
  {
    printf("%d\n", exercio(num));
  }
  return(0);
}
