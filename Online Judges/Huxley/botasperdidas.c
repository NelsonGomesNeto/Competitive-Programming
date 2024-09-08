#include <stdio.h>

int main()
{
  int sapatos, ler, check, quant;
  while (scanf("%d", &sapatos) && sapatos != -1)
  {
    quant = 0;
    int num[sapatos]; char lado[sapatos];
    for (ler = 0; ler < sapatos; ler ++)
    {
      scanf("%d %c", &num[ler], &lado[ler]);
      //printf("%d %c\n", num[ler], lado[ler]);
    }
    for (ler = 0; ler < sapatos; ler ++)
    {
      for (check = ler + 1; check < sapatos; check ++)
      {
        if (num[ler] == num[check] && ((lado[ler] == lado[check] + 1) || (lado[ler] == lado[check] - 1)))
        {
          //printf("%d %c ~~ %d %c\n", num[ler], lado[ler], num[check], lado[check]);
          quant ++;
          num[check] = - check;
          check = sapatos;
        }
      }
    }
    printf("%d\n", quant);
  }
  return(0);
}
