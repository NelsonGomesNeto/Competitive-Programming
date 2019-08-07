#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 5e4; int n;
struct Point
{
  int x, y;
  bool operator<(const Point &p) const { return(x < p.x || (x == p.x && y < p.y)); }
};
map<Point, int> allPoints;
Point points[maxN];
vector<int> graph[maxN];
int color[maxN], cnt[2];

void dfs(int u, int prv = -1, int c = 0)
{
  if (color[u] != -1) return;
  color[u] = c, cnt[c] ++;
  for (int v: graph[u])
    if (v != prv)
      dfs(v, u, 1 - c);
}

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i ++)
  {
    scanf("%d %d", &points[i].x, &points[i].y);
    allPoints[points[i]] = i;
  }

  for (int i = 0; i < n; i ++)
    for (int dx = 0; dx <= 5; dx ++)
      for (int dy = -5; dy <= 5; dy ++)
      {
        int d = dx*dx + dy*dy;
        if (d == 0 || d > 25) continue;
        Point closePoint = {points[i].x + dx, points[i].y + dy};
        if (allPoints.count(closePoint))
        {
          int j = allPoints[closePoint];
          graph[i].push_back(j), graph[j].push_back(i);
        }
      }

  memset(color, -1, sizeof(color));
  int ans = 0;
  for (int i = 0; i < n; i ++)
    if (color[i] == -1)
    {
      cnt[0] = cnt[1] = 0;
      dfs(i);
      ans += min(cnt[0], cnt[1]);
    }
  printf("%d\n", ans);

  return(0);
}