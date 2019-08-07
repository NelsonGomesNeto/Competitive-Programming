#include <bits/stdc++.h>
char x[100001], y[100001];

int hammingDistance()
{
  int hamming = 0;
  for (int i = 0; y[i]; i ++)
    hamming += x[i] != y[i];
  return(hamming);
}

int main()
{
  scanf("%s", x);
  int k, pos = 0, best = 1<<20; scanf("%d", &k);
  for (int i = 0; i < 5; i ++)
  {
    getchar();
    scanf("%s", y);
    int hamming = hammingDistance();
    if (hamming < best)
    {
      best = hamming;
      pos = i + 1;
    }
  }

  if (best <= k)
    printf("%d\n%d\n", pos, best);
  else
    printf("-1\n");

  return(0);
}