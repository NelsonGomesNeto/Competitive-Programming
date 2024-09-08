#include <stdio.h>

int main()
{
  int num[4], i;
  for (i = 0; i < 4; i ++)
  {
    scanf("%d", &num[i]);
  }
  int o, b, aux;
  for (o = 0; o < 4; o ++)
  {
    for (b = o; b < 4; b ++)
    {
      if (num[o] < num [b])
      {
        aux = num[o];
        num[o] = num[b];
        num[b] = aux;
      }
    }
  }
  for (o = 0; o < 3; o ++)
  {
    printf("%d ", num[o]);
  } printf("%d\n", num[o]);
  return(0);
}
