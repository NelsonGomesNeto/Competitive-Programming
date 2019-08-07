#include <bits/stdc++.h>

int main()
{
  int n;
  while (scanf("%d", &n) && n)
  {
    int vote[n], v; memset(vote, 0, sizeof(vote));
    for (int i = 0; i < n; i ++)
      for (int j = 0; j < n; j ++)
      {
        scanf("%d", &v);
        vote[j] += v;
      }

    int winner = 0;
    for (int i = 0; i < n; i ++)
      if (vote[i] > winner)
        winner = vote[i];

    printf("%d\n", winner);
  }
  return(0);
}