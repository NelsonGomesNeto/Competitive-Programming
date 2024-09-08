#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int n, m, x;
  while (scanf("%d %d %d", &n, &m, &x) != EOF)
  {
    int c[n], a[n][m];
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &c[i]);
      for (int j = 0; j < m; j++)
        scanf("%d", &a[i][j]);
    }
    int ans = 1e9;
    for (int bit = 0, end = 1 << n; bit < end; bit++)
    {
      int cost = 0, level[m]; memset(level, 0, sizeof(level));
      for (int i = 0; i < n; i++)
        if (bit & (1 << i))
        {
          cost += c[i];
          for (int j = 0; j < m; j++)
            level[j] += a[i][j];
        }
      bool can = true;
      for (int j = 0; j < m; j++)
        if (level[j] < x)
          can = false;
      if (can)
        ans = min(ans, cost);
    }
    if (ans == 1e9) ans = -1;
    printf("%d\n", ans);
  }
  return 0;
}