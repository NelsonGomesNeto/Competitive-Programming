#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e6; int n, m;
char ss[maxN + 1];
vector<string> mat, grid;
vector<bool> visited[maxN];
int flips[maxN], accf[maxN + 1], acce[maxN + 1];

int di[2] = {0, 1}, dj[2] = {1, 0};
void bfs(int si, int sj)
{
  queue<pair<int, int>> q;
  q.push({si, sj});
  while (!q.empty())
  {
    int i = q.front().first, j = q.front().second; q.pop();
    visited[i][j] = true;
    grid[i][j] = 'E';
    for (int d = 0; d < 2; d++)
    {
      int ni = i + di[d], nj = j + dj[d];
      if (ni < n && nj < m && mat[ni][nj] == '.')
        q.push(make_pair(ni, nj));
    }
  }
}

int main()
{
  while (~scanf("%d %d", &n, &m))
  {
    mat.clear();
    for (int i = 0; i < n; i++)
    {
      scanf(" %s", ss);
      mat.push_back(string(ss));
      visited[i].clear();
      visited[i].resize(m, false);
    }
    grid = mat;
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) grid[i][j] = 'N';

    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++)
      if (!visited[i][j] && mat[i][j] == '.')
        bfs(i, j);

    DEBUG {
      for (int i = 0; i < n; i++)
        printf("\t%s\n", grid[i].c_str());
    }

    for (int j = 0; j < m; j++)
    {
      flips[j] = 0;
      for (int i = 1; i < n; i++)
        if (grid[i - 1][j] != grid[i][j])
          flips[j]++;
      accf[j + 1] = accf[j] + (flips[j] > 2);
      acce[j + 1] = acce[j] + (grid[n - 1][j] == 'E');
    }

    int q; scanf("%d", &q);
    for (int qq = 1; qq <= q; qq++)
    {
      int l, r; scanf("%d %d", &l, &r); l--, r--;
      int fs = accf[r + 1] - accf[l];
      int es = acce[r + 1] - acce[l];
      if (fs || es == 0) printf("NO\n");
      else printf("YES\n");
    }
  }
  return 0;
}
