#include <stdio.h>
#include <stdlib.h>

int main()
{
  int candidatos, i;
  while (scanf("%d", &candidatos) && candidatos != 0)
  {
    int *ida = malloc(1 * sizeof(int)), idaSize = 0;
    int go, back, ok = 0;
    for (i = 0; i < candidatos; i ++)
    {
      scanf("%d %d", &go, &back);
      if (back <= idaSize && ida[back] == go)
      {
        ok += 2;
        continue;
      }
      if (go >= idaSize)
      {
        ida = realloc(ida, (go + 1) * sizeof(int));
        idaSize = go;
      }
      ida[go] = back;
    }
    if (ok == candidatos)
    {
      printf("YES\n");
    }
    else
    {
      printf("NO\n");
    }
    free(ida);
  }
  return(0);
}
