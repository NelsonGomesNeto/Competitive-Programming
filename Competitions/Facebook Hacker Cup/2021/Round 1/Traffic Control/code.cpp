#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 50; int n, m, a, b;
int ans[maxN][maxN];

int di[4] = {0, 0, -1, 1}, dj[4] = {1, -1, 0, 0};
int dist[maxN][maxN];
int dijkstra(int si, int sj, int ei, int ej)
{
  for (int i = 0; i < n; i++) fill(dist[i], dist[i]+m, 1e8);
  priority_queue<pair<int, pair<int, int>>> pq;
  dist[si][sj] = ans[si][sj];
  pq.push({-dist[si][sj], {si, sj}});
  while (!pq.empty())
  {
    int ui = pq.top().second.first, uj = pq.top().second.second, d = -pq.top().first; pq.pop();
    if (dist[ui][uj] < d) continue;

    for (int k = 0; k < 4; k++)
    {
      int ni = ui + di[k], nj = uj + dj[k];
      if (ni >= 0 && nj >= 0 && ni < n && nj < m && d + ans[ni][nj] < dist[ni][nj])
      {
        dist[ni][nj] = d + ans[ni][nj];
        pq.push({-dist[ni][nj], {ni, nj}});
      }
    }
  }
  return dist[ei][ej];
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d %d %d", &n, &m, &a, &b);
    bool can = true;

    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        ans[i][j] = 1e3;
    for (int i = 0; i < n; i++)
      ans[i][0] = ans[i][m - 1] = 1;
    for (int j = 0; j < m; j++)
      ans[n - 1][j] = 1;
    ans[0][0] = a - (n - 1) - (m - 1);
    ans[0][m - 1] = b - (n - 1) - (m - 1);

    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        if (ans[i][j] < 1 || ans[i][j] > 1e3)
          can = false;

    if (can)
    {
      int aa = dijkstra(0, 0, n - 1, m - 1);
      if (aa != a) can = false;

      int bb = dijkstra(n - 1, 0, 0, m - 1);
      if (bb != b) can = false;
      DEBUG printf("%d %d | %d %d\n", a, aa, b, bb);
    }

    printf("Case #%d: %s\n", tt, can ? "Possible" : "Impossible");
    if (can)
    {
      for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
          printf("%d%s", ans[i][j], j < m - 1 ? " " : "\n");
    }
  }
  return 0;
}