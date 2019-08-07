#include <bits/stdc++.h>
using namespace std;

int solve(int slice[], int n)
{
  int now = 0, best = 360;
  for (int j = 0; j < n; j ++)
  {
    now = 0;
    for (int i = j, all = 0; all < 2*n; i ++, all ++)
    {
      i %= n;
      now += slice[i];
      if (abs((360 - now) - now) < best)
      best = abs((360 - now) - now);
    }
  }
  return(best);
}

int main()
{
  int n; scanf("%d", &n);
  int slice[n];
  for (int i = 0; i < n; i ++)
    scanf("%d", &slice[i]);

  int best = solve(slice, n);

  printf("%d\n", best);

  return(0);
}