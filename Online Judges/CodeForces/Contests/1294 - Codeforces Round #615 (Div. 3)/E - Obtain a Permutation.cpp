#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n, m;
vector<vector<int>> mat;
int cnt[maxN];

int circularFix(int pos, int mod)
{
  return ((pos % mod) + mod) % mod;
}

int main()
{
  while (scanf("%d %d", &n, &m) != EOF)
  {
    mat.clear();
    mat.resize(n, vector<int>(m));
    for (int i = 0; i < n; i ++)
      for (int j = 0; j < m; j ++)
      {
        scanf("%d", &mat[i][j]);
        mat[i][j] -= j + 1;
      }

    DEBUG
    {
      for (int i = 0; i < n; i ++)
        for (int j = 0; j < m; j ++)
          printf("%d%c", mat[i][j], j < m - 1 ? ' ' : '\n');
      for (int i = 0; i < n; i ++)
        printf("%d%c", i*m, i < n - 1 ? ' ' : '\n');
    }

    int ans = 0;
    for (int j = 0; j < m; j ++)
    {
      for (int i = 0; i < n; i ++) cnt[i] = 0;

      for (int i = 0; i < n; i ++)
        if (mat[i][j] >= 0 && mat[i][j] % m == 0 && mat[i][j] / m < n)
          cnt[circularFix(i - mat[i][j] / m, n)] ++;
      int cheapest = n;
      for (int i = 0; i < n; i ++)
        cheapest = min(cheapest, i + (n - cnt[i]));
      ans += cheapest;
      DEBUG printf("\t%d %d\n", j, cheapest);
    }
    printf("%d\n", ans);
  }
  return 0;
}
