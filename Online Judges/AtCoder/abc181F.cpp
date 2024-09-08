#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e2; int n;
const double eps = 1e-7;
struct Point
{
  double x, y;
  void read() { scanf("%lf %lf", &x, &y); }
  double dist(Point &other) { return sqrt((x - other.x)*(x - other.x) + (y - other.y)*(y - other.y)); }
};
Point points[maxN];

int parent[maxN + 2]; // + up and down
int up, down;
int root(int u)
{
  return parent[u] < 0 ? u : parent[u] = root(parent[u]);
}
void merge(int u, int v)
{
  u = root(u), v = root(v);
  if (u == v) return;
  if (parent[u] > parent[v]) swap(u, v);
  parent[u] += parent[v];
  parent[v] = u;
}

bool can(double r)
{
  memset(parent, -1, sizeof(parent));
  double maxDist = 2*r;

  for (int i = 0; i < n; i++)
  {
    if (100 - points[i].y <= maxDist)
      merge(i, up);
    if (points[i].y - (-100) <= maxDist)
      merge(i, down);

    for (int j = i + 1; j < n; j++)
      if (points[i].dist(points[j]) <= maxDist)
        merge(i, j);
  }

  for (int i = 0; i < n; i++)
    if (root(i) == root(up) && root(i) == root(down))
      return false;
  return true;
}
double binarySearch(double lo = 0, double hi = 100)
{
  while (abs(hi - lo) >= eps)
  {
    double mid = (lo + hi) / 2;
    if (can(mid)) lo = mid;
    else hi = mid;
  }
  return hi;
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    up = n, down = n + 1;

    for (int i = 0; i < n; i++)
      points[i].read();

    double ans = binarySearch();
    printf("%.15lf\n", ans);
  }
  return 0;
}