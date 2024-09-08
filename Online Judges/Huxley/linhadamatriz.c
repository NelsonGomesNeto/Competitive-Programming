#include <stdio.h>

int main()
{
  float matriz[12][12], total = 0; int linha, x, y; char oper;
  scanf("%d", &linha);
  getchar(); scanf("%c", &oper);
  for (y = 0; y < 12; y ++)
  {
    for (x = 0; x < 12; x ++)
    {
      scanf("%f", &matriz[x][y]);
    }
  }
  for (x = 0; x < 12; x ++)
  {
    total += matriz[x][linha];
  }
  if (oper == 'M' || oper == 'm')
  {
    printf("%.1lf\n", total / 12);
  }
  else
  {
    printf("%.1lf\n", total);
  }
  return(0);
}
