#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
  int a, b; scanf("%d %d", &a, &b);
  char stringA[a + 10], stringB[b + 10];
  scanf(" %s", stringA);
  scanf(" %s", stringB);

  int i, j, k, cont, smallest = a + 10;
  int ans[a];
  for (i = 0; i < b; i ++)
  {
    int aux[a];
    if (b - i >= a)
      for (j = 0, k = i, cont = 0; j < a && k < b; j ++, k ++)
      {
        if (stringA[j] != stringB[k])
          aux[cont ++] = j + 1;
      }

    if (cont < smallest)
    {
      smallest = cont;
      for (k = 0; k < smallest; k ++)
        ans[k] = aux[k];
    }
  }

  printf("%d\n", smallest);
  if (smallest > 0)
  {
    i = 0;
    for (; i < smallest - 1; i ++)
      printf("%d ", ans[i]);
    printf("%d\n", ans[i]);
  }
  else
    printf("\n");

  return(0);
}
