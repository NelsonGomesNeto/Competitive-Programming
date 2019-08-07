#include <stdio.h>

int max(int a, int b)
{
  return(a > b ? a : b);
}

int min(int a, int b)
{
  return(a < b ? a : b);
}

int main()
{
  int sections; scanf("%d", &sections);
  int pool[sections + 2], before[sections + 2], after[sections + 2], i, total = 0;
  for (i = 1; i <= sections; i ++)
    scanf("%d", &pool[i]);

  before[sections + 1] = before[0] = 0;
  for (i = 1; i <= sections; i ++)
    before[i] = max(before[i - 1], pool[i]);

  after[sections + 1] = after[0] = 0;
  for (i = sections; i >= 1; i --)
    after[i] = max(after[i + 1], pool[i]);

  for (i = 1; i <= sections; i ++)
    if (pool[i] < min(before[i - 1], after[i + 1]))
      total ++;

  printf("%d\n", total);

  return(0);
}
