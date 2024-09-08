#include <stdio.h>

int main()
{
  float quanti[4][4], preco[3]; int i, j;
  for (j = 0; j < 4; j ++)
  {
    for (i = 0; i < 4; i ++)
    {
      scanf("%f", &quanti[i][j]);
    }
  }
  for (i = 0; i < 3; i ++)
  {
    preco[i] = (quanti[0][i] * quanti[0][3]) + (quanti[1][i] * quanti[1][3]) + (quanti[2][i] * quanti[2][3]) + (quanti[3][i] * quanti[3][3]);
    printf("%.2f\n", preco[i]);
  }
  return(0);
}
