#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n, t; scanf("%d %d", &n, &t);
  int bus[n][2]; for (int i = 0; i < n; i ++) scanf("%d %d", &bus[i][0], &bus[i][1]);

  int best = -1, bb = 0;
  for (int i = 0; i < n; i ++)
    for (int j = 0; ; j ++)
    {
      int tt = bus[i][0] + bus[i][1]*j;
      if (tt >= t && (best == -1 || tt < best))
        best = tt, bb = i;
      if (tt >= t) break;
    }
  printf("%d\n", bb + 1);

  return(0);
}