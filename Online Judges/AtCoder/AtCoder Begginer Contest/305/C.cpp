#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int di[4] = {1, 0, -1, 0};
const int dj[4] = {0, 1, 0, -1};
const int maxN = 5e2;
int n, m;
char ss[maxN + 1];
string mat[maxN];


int main()
{
  while (~scanf("%d %d", &n, &m))
  {
    for (int i = 0; i < n; ++i)
    {
      scanf(" %s", ss);
      mat[i] = string(ss);
    }

    pair<int, int> ans;
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
        if (mat[i][j] == '.')
        {
          int adjacentCookiesCnt = 0;
          for (int d = 0; d < 4; ++d)
          {
            int ni = i + di[d], nj = j + dj[d];
            if (ni < 0 || nj < 0 || ni >= n || nj >= m || mat[ni][nj] != '#') continue;
            ++adjacentCookiesCnt;
          }
          if (adjacentCookiesCnt >= 2)
            ans = make_pair(i, j);
        }
    printf("%d %d\n", ans.first + 1, ans.second + 1);
  }
  return 0;
}
