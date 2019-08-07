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
  int blocks; scanf("%d", &blocks);
  int f[blocks + 2], left[blocks + 2], right[blocks + 2], i;
  for (i = 1; i <= blocks; i ++)
    scanf("%d", &f[i]);

  left[1] = left[blocks] = 1;
  for (i = 1; i < blocks; i ++)
    left[i + 1] = min(left[i] + 1, f[i + 1]);

  right[1] = right[blocks] = 1;
  for (i = blocks; i >= 0; i --)
    right[i - 1] = min(right[i] + 1, f[i - 1]);

  int best = 1;
  for (i = 1; i <= blocks; i ++)
    best = max(best, min(left[i], right[i]));

  printf("%d\n", best);

  return(0);
}
