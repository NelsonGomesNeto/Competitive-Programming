#include <stdio.h>

int main()
{
  int size; scanf("%d", &size);
  int a[size][size], i, j;
  for (i = 0; i < size; i ++)
    for (j = 0; j < size; j ++)
      scanf("%d", &a[i][j]);

  int k, m, one;
  for (i = 0; i < size; i ++)
    for (j = 0; j < size; j ++)
      if (a[i][j] != 1)
      {
        one = 0;
        for (k = 0; k < size; k ++)
          for (m = 0; m < size; m ++)
            if (a[i][j] == a[k][j] + a[i][m])
              one = 1;
            //printf("%d %d | %d %d %d\n", i, j, a[i][j], a[k][j], a[i][m]);
        if (one == 0)
        {
          printf("No\n");
          return(0);
        }
      }

  printf("Yes\n");

  return(0);
}
