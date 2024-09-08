#include <stdio.h>

int main()
{
  int testes; scanf("%d", &testes);
  while (testes > 0)
  {
    int angulo; scanf("%d", &angulo);
    if (-360 % (angulo - 180) == 0)
    {
      printf("SIM\n");
    }
    else
    {
      printf("NAO\n");
    }
    testes --;
  }
  return(0);
}
