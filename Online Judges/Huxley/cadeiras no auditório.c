#include <stdio.h>

int main()
{
  int L, C; scanf("%d %d", &L, &C);
  int cadeira[L][C], i, j, final[L][C];
  for (j = 0; j < L; j ++)
  {
    for (i = 0; i < C; i ++)
    {
      scanf("%d", final[j][i]);
      cadeira[j][i] = (i - 1) * C + j;
    }
  }
  return(0);
}
