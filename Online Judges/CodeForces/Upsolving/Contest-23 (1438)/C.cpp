#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e2; int n, m;
bool done[maxN][maxN];
int a[maxN][maxN];

int di[4] = {0, 0, -1, 1}, dj[4] = {-1, 1, 0, 0};

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d", &n, &m);
    vector<pair<int, pair<int, int>>> positions;
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
      {
        scanf("%d", &a[i][j]);
        positions.push_back({a[i][j], {i, j}});
      }
    sort(positions.begin(), positions.end());
    reverse(positions.begin(), positions.end());

    memset(done, false, sizeof(done));
    for (int required = 4; required >= 1; required--)
    // for (int required = 1; required <= 4; required++)
    {
      for (int hehe = 0; hehe < 10; hehe++)
        for (auto &p: positions)
        {
          int i = p.second.first, j = p.second.second;
          if (!done[i][j])
          {
            int has = 0;
            for (int k = 0; k < 4; k++)
            {
              int ni = i + di[k], nj = j + dj[k];
              if (ni >= 0 && ni < n && nj >= 0 && nj < m && a[i][j] == a[ni][nj])
                has++;
            }
            if (has == required)
            {
              for (int k = 0; k < 4; k++)
              {
                int ni = i + di[k], nj = j + dj[k];
                if (ni >= 0 && ni < n && nj >= 0 && nj < m && a[i][j] == a[ni][nj])
                  done[ni][nj] = true, a[ni][nj]++;
              }
              // a[i][j]++, done[i][j] = true;
            }
          }
        }
    }
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        printf("%d%c", a[i][j], j < m - 1 ? ' ' : '\n');
  }
  return 0;
}