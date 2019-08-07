#include <stdio.h>

int main()
{
  int tamanhoBarra, precos; scanf("%d %d", &tamanhoBarra, &precos);

  int biggest = -1, quantos = 0;
  int table[2][precos], i;
  for (i = 0; i < precos; i ++)
  {
    scanf("%d", &table[0][i]);
    if (i + 1 == tamanhoBarra)
    {
      biggest = table[0][i]; quantos = 1;
    }
  }
  for (i = 0; i < precos; i ++)
  {
    scanf("%d", &table[1][i]);
    if (table[1][i] == biggest)
      quantos ++;
    if (i + 1 == tamanhoBarra && table[1][i] > biggest)
    {
      biggest = table[1][i]; quantos = 1;
    }
  }
  
  int j = tamanhoBarra - 2; i = 0;
  while (j >= precos)
  {
    j --;
    i ++;
  }
  for (; i < tamanhoBarra - 1 && i < precos && j >= 0; i ++, j --)
  {
    if (table[0][i] + table[1][j] == biggest)
      quantos ++;

    if (table[0][i] + table[1][j] > biggest)
    {
      biggest = table[0][i] + table[1][j]; quantos = 1;
    }
  }

  printf("%d\n%d\n", quantos, biggest);
  return(0);
}
