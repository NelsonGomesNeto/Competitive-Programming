#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int t;
  while (scanf("%d", &t) != EOF)
  {
    for (int tt = 1; tt <= t; tt++)
    {
      int n; scanf("%d", &n);
      int nums[2][2]; memset(nums, 0, sizeof(nums));
      int g[2]; memset(g, 0, sizeof(g));
      for (int i = 1; i <= n; i++)
      {
        int x; scanf("%1d", &x);
        nums[i & 1][x & 1]++;
        g[x & 1]++;
      }

      for (int i = 1; i < n; i++)
      {
        if (i & 1) // Raze
        {
          if (nums[1][0]) nums[1][0]--, g[0]--;
          else if (nums[1][1]) nums[1][1]--, g[1]--;
        }
        else
        {
          if (nums[0][1]) nums[0][1]--, g[1]--;
          else if (nums[0][0]) nums[0][0]--, g[0]--;
        }
        DEBUG printf("\t%d %d %d\n", i, g[0], g[1]);
      }

      printf("%d\n", g[1] ? 1 : 2);
    }
  }
  return 0;
}
