#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3; int n, m;
char mat[maxN][maxN + 1];
vector<set<pair<int, int>>> blocks;

int di[4] = {0, 0, 1, -1}, dj[4] = {1, -1, 0, 0};
void dfs(int i, int j)
{
  if (i < 0 || j < 0 || i >= n || j >= m || mat[i][j] != '#') return;
  blocks.back().insert({i, j});
  mat[i][j] = '.';
  for (int k = 0; k < 4; k++)
    dfs(i + di[k], j + dj[k]);
}

int main()
{
  while (scanf("%d %d", &n, &m) != EOF)
  {
    blocks.clear();
    for (int i = 0; i < n; i++)
      scanf(" %s", mat[i]);

    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        if (mat[i][j] == '#')
        {
          blocks.push_back(set<pair<int, int>>());
          dfs(i, j);
        }

    bool can = true;
    bool r[n], c[m]; memset(r, false, sizeof(r)), memset(c, false, sizeof(c));
    for (auto &b: blocks)
    {
      int minR = n, maxR = -1, minC = m, maxC = -1;
      DEBUG printf("\tblock\n");
      for (auto &p: b)
      {
        DEBUG printf("\t\t%d %d\n", p.first, p.second);
        r[p.first] = true, c[p.second] = true;
        minR = min(minR, p.first), maxR = max(maxR, p.first);
        minC = min(minC, p.second), maxC = max(maxC, p.second);
      }

      for (int j = minC; j <= maxC; j++)
        for (int i = minR; i <= maxR; i++)
          if (b.count({i, j}))
          {
            int ii = i;
            while (ii <= maxR && b.count({ii, j})) ii++;
            // hole here
            while (ii <= maxR && !b.count({ii, j})) ii++;
            DEBUG printf("c %d | %d - %d\n", j, i, ii);
            if (ii <= maxR) can = false;
            i = ii;
          }
      for (int i = minR; i <= maxR; i++)
        for (int j = minC; j <= maxC; j++)
          if (b.count({i, j}))
          {
            int jj = j;
            while (jj <= maxC && b.count({i, jj})) jj++;
            // hole here
            while (jj <= maxC && !b.count({i, jj})) jj++;
            DEBUG printf("r %d | %d - %d\n", i, j, jj);
            if (jj <= maxC) can = false;
            j = jj;
          }
    }
    for (int i = 0; i < n; i++) if (!r[i]) can = false;
    for (int i = 0; i < m; i++) if (!c[i]) can = false;
    if (blocks.empty()) can = true;

    printf("%d\n", can ? (int)blocks.size() : -1);
  }
  return 0;
}
