#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 5e3; int n;
const double pi = acos(-1);
vector<int> tree[maxN];

struct Point
{
  double x, y;
  Point operator+(Point other) { return Point{x + other.x, y + other.y}; }
  double dist(const Point &other) { return sqrt((x - other.x)*(x - other.x) + (y - other.y)*(y - other.y)); }
};
Point pos[maxN];

void dfs(int u = 0, int prv = -1, Point now = {0, 0})
{
  pos[u] = now;
  double angleSpacing = 2*pi / max(1, (int)(tree[u].size() - (prv != -1)));
  if (prv != -1) angleSpacing = pi / max(1, (int)(tree[u].size() - (prv != -1)));
  DEBUG printf("%lf\n", angleSpacing);
  int i = 1;
  for (int v: tree[u])
  {
    if (v != prv)
    {
      if (prv != -1)
        dfs(v, u, now + Point{cos(i * angleSpacing - pi), sin(i * angleSpacing - pi)});
      else
        dfs(v, u, now + Point{cos(i * angleSpacing), sin(i * angleSpacing)});
      i ++;
    }
  }
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i++) tree[i].clear();

    for (int i = 1; i < n; i++)
    {
      int p; scanf("%d", &p); p--;
      tree[p].push_back(i);
      tree[i].push_back(p);
    }

    double ans = 0;
    dfs();

    DEBUG
      for (int i = 0; i < n; i++)
        printf("%d - %lf %lf\n", i, pos[i].x, pos[i].y);

    for (int i = 0; i < n; i++)
      for (int j = i + 1; j < n; j++)
      {
        double dist = pos[i].dist(pos[j]);
        ans += dist * dist;
      }
    printf("%.15lf\n", ans);
  }
  return 0;
}