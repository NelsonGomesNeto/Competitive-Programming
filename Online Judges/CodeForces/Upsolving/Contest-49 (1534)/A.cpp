#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    int n, m; scanf("%d %d", &n, &m);
    char mat[n][m + 1], ans[n][m + 1];
    for (int i = 0; i < n; i++)
    {
      scanf(" %s", mat[i]);
      for (int j = 0; j <= m; j++)
        ans[i][j] = mat[i][j];
    }

    bool can = false;
    for (int k = 0; k < 2; k++)
    {
      can = true;
      for (int i = 0; i < n; i++)
      {
        for (int j = 0; j < m; j++)
        {
          ans[i][j] = k ? ((i + j) & 1 ? 'W' : 'R') : ((i + j) & 1 ? 'R' : 'W');
          if (mat[i][j] != '.' && ans[i][j] != mat[i][j])
            can = false;
        }
      }
      if (can) break;
    }

    if (!can) printf("NO\n");
    else
    {
      printf("YES\n");
      for (int i = 0; i < n; i++) printf("%s\n", ans[i]);
    }
  }
  return 0;
}
