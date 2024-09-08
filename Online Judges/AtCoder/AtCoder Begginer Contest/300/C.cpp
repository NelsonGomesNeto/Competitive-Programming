#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int di[4] = {1, 1, -1, -1};
int dj[4] = {-1, 1, -1, 1};

const int maxN = 100;
int n, m;
char ss[maxN + 1];
string c[maxN];

int ans[maxN];

int main()
{
  while (~scanf("%d %d", &n, &m))
  {
    memset(ans, 0, sizeof(ans));
    for (int i = 0; i < n; ++i)
    {
      scanf(" %s", ss);
      c[i] = string(ss);
    }

    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
        if (c[i][j] == '#')
        {
          int sz = 1, res = 0;
          while (true)
          {
            bool valid = true;
            for (int d = 0; d < 4; ++d)
            {
              int ni = i + sz * di[d];
              int nj = j + sz * dj[d];
              if (ni < 0 || nj < 0 || ni >= n || nj >= m || c[ni][nj] != '#')
                valid = false;
            }
            if (valid)
            {
              res = sz;
              ++sz;
            }
            else break;
          }
          if (res)
            ++ans[res - 1];
        }

    int nm = min(n, m);
    for (int i = 0; i < nm; ++i)
      printf("%d%c", ans[i], i + 1 < nm ? ' ' : '\n');
  }
  return 0;
}
