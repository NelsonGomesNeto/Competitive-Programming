#include <stdio.h>
#include <stdlib.h>

int main()
{
  int tam; scanf("%d", &tam);
  int i, j, num;
  for (i = 1; i <= tam; i ++)
  {
    num = 1;
    for (j = 1; j < tam; j ++)
    {
      printf("%d ", num);
      if (i > j)
      {
        num ++;
      }
    } printf("%d\n", num);
  }
  return(0);
}
