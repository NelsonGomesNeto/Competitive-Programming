#include <stdio.h>
#include <string.h>

int min(int a, int b)
{
  return(a < b ? a : b);
}

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    int n; scanf("%d", &n);
    char ingredient[n][41]; int i, j;
    int ingredientMap[n][256];
    for (i = 0; i < n; i ++)
    {
      scanf("\n%s", ingredient[i]); memset(ingredientMap[i], 0, 256*sizeof(int));
      for (j = 0; ingredient[i][j]; j ++)
        ingredientMap[i][ingredient[i][j]] ++;
    }
    char has[10000 + 1]; scanf("\n%s", has);
    int hasMap[256]; memset(hasMap, 0, sizeof(hasMap));
    for (i = 0; has[i]; i ++)
      hasMap[has[i]] ++;

    for (i = 0; i < n; i ++)
    {
      int can = 999999;
      for (j = 0; j < 256; j ++)
        if (ingredientMap[i][j])
        {
          can = min(can, hasMap[j] / ingredientMap[i][j]);
          // printf("%c has: %d, ingredient: %d\n", j, hasMap[j], ingredientMap[i][j]);
        }
      for (j = 0; j < 256; j ++)
        hasMap[j] -= ingredientMap[i][j] * can;
      printf("%d\n", can);
    }
    if (t) printf("\n");
  }
  return(0);
}
