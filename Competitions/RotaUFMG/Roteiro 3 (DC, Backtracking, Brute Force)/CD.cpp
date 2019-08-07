#include <bits/stdc++.h>
int bestCD[21], best, bestSize;

void binPack(int length[], int cd[], int size, int i, int n)
{
  if (i == -1)
  {
    if (n < best)
    {
      memcpy(bestCD, cd, sizeof(bestCD));
      best = n; bestSize = size;
    }
    return;
  }

  if (n - length[i] >= 0)
  {
    cd[size] = length[i];
    binPack(length, cd, size + 1, i - 1, n - length[i]);
  }
  binPack(length, cd, size, i - 1, n);
}

int main()
{
  int n, tracks;
  while (scanf("%d %d", &n, &tracks) != EOF)
  {
    best = 1<<20;
    int length[tracks];
    for (int i = 0; i < tracks; i ++)
      scanf("%d", &length[i]);

    int cd[tracks];
    binPack(length, cd, 0, tracks - 1, n);
    for (int i = bestSize - 1; i >= 0; i --)
      printf("%d ", bestCD[i]);
    printf("sum:%d\n", n - best);
  }
  return(0);
}