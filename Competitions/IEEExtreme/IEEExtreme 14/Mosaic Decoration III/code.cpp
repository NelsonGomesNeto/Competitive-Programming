#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e6; int n, m, r, c;
const lli inf = 1e18;
vector<vector<lli>> pattern;

int main()
{
  while (scanf("%d %d %d %d", &n, &m, &r, &c) != EOF)
  {
    pattern.resize(r, vector<lli>(c));
    lli fullPatternCost = 0;
    for (int i = 0; i < r; i++)
      for (int j = 0; j < c; j++)
      {
        scanf("%lld", &pattern[i][j]);
        fullPatternCost += pattern[i][j];
      }

    lli ans = inf;
    for (int i = 0; i <= min(n, r - 1); i++)
      for (int j = 0; j <= min(m, c - 1); j++)
      {
        lli cost = 0;
        for (int ii = 0; ii < r; ii++)
          for (int jj = 0; jj < c; jj++)
          {
            lli hstart = (jj + j) % c;
            lli horizontal = (m - hstart) / c + ((m - hstart) % c != 0);
            lli vstart = (ii + i) % r;
            lli vertical = (n - vstart) / r + ((n - vstart) % r != 0);
            lli res = horizontal * vertical * pattern[ii][jj];
            cost += res;
            DEBUG printf("\t%d %d - %lld %lld - %lld %lld - %lld\n", ii, jj, vstart, hstart, vertical, horizontal, res);
          }
        DEBUG printf("%d %d | %lld\n", i, j, cost);

        ans = min(ans, cost);
      }

    printf("%lld\n", ans);
  }
  return 0;
}