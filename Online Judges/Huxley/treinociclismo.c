#include <stdio.h>

int main()
{
  int repeat = 7, viva = 0;
  float KmD;
  while (repeat > 0)
  {
    scanf("%f", &KmD);
    if (KmD >= 8)
    {
      viva ++;
    }
    repeat --;
  }
  if (viva >= 5)
  {
    printf("Desempenho otimo\n");
  }
  else if (viva < 3)
  {
    printf("Desempenho ruim\n");
  }
  else
  {
    printf("Desempenho razoavel\n");
  }
  return(0);
}
