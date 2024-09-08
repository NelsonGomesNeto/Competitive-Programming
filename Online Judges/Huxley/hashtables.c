#include <stdio.h>
#include <stdlib.h>

int main()
{
  int tests; scanf("%d", &tests);
  while (tests > 0)
  {
    int hash, keys; scanf("%d %d", &hash, &keys);
    int **table = calloc(hash, sizeof(*table));
    int i, j, chave;
    for (i = 0; i < hash; i ++)
    {
      table[i] = calloc(1, sizeof(**table));
      //printf("%d\n", table[i][0]);
    }
    for (i = 0; i < keys; i ++)
    {
      scanf("%d", &chave);
      int pos = chave % hash;
      //printf("%d\n", pos);
      table[pos][0] ++;
      table[pos] = realloc(table[pos], (table[pos][0] + 1) * sizeof(**table));
      table[pos][table[pos][0]] = chave;
    }
    for (i = 0; i < hash; i ++)
    {
      printf("%d", i);
      for (j = 1; j <= table[i][0]; j ++)
      {
        printf(" -> %d", table[i][j]);
      } printf(" -> \\\n");
    }
    tests --;
    if (tests != 0)
    {
      printf("\n");
    }
    free(table);
  }
  return(0);
}
