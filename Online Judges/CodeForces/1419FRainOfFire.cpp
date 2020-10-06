#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3; int n;
const lli inf = 2e9 + 1;
struct Point
{
  lli x, y;
  void read() { scanf("%lld %lld", &x, &y); }
  bool sameLine(Point &other) { return x == other.x || y == other.y; }
  lli dist(Point &other) { return abs(x - other.x) + abs(y - other.y); }
  bool operator<(const Point &other) const { return x < other.x || (x == other.x && y < other.y); }
  bool operator==(const Point &other) const { return x == other.x && y == other.y; }
};
Point points[maxN];
vector<Point> trialPoints;
vector<lli> ux, uy;

vector<int> graph[maxN];

bool visited[maxN];
vector<unordered_map<lli, pair<lli, lli>>> xs, ys;
vector<vector<int>> components;
void dfs(int u)
{
  if (visited[u]) return;
  visited[u] = true;

  components.back().push_back(u);

  if (!xs.back().count(points[u].x)) xs.back()[points[u].x] = {inf, -inf};
  xs.back()[points[u].x].first = min(xs.back()[points[u].x].first, points[u].y);
  xs.back()[points[u].x].second = max(xs.back()[points[u].x].second, points[u].y);

  if (!ys.back().count(points[u].y)) ys.back()[points[u].y] = {inf, -inf};
  ys.back()[points[u].y].first = min(ys.back()[points[u].y].first, points[u].x);
  ys.back()[points[u].y].second = max(ys.back()[points[u].y].second, points[u].x);

  for (int v: graph[u])
    dfs(v);
}

bool checkWithAdditional(vector<Point> &ps, lli t)
{
  for (Point &np: ps)
  {
    bool valid = true;
    for (int k = 0; k < xs.size(); k++)
    {
      DEBUG printf("\t\t(%lld, %lld) - %d %d - %lld %lld || %lld || %d %d\n", np.x, np.y, (int)xs[k].count(np.x), (int)ys[k].count(np.y),
        xs[k].count(np.x) ? min(abs(np.y - xs[k][np.x].first),
                                abs(np.y - xs[k][np.x].second)) : inf,
        ys[k].count(np.y) ? min(abs(np.x - ys[k][np.y].first),
                                     abs(np.x - ys[k][np.y].second)) : inf,
        t,
        (xs[k].count(np.x) && min(abs(np.y - xs[k][np.x].first),
                                     abs(np.y - xs[k][np.x].second)) <= t),
        (ys[k].count(np.y) && min(abs(np.x - ys[k][np.y].first),
                                     abs(np.x - ys[k][np.y].second)) <= t));

      if (!(xs[k].count(np.x) && min(abs(np.y - xs[k][np.x].first),
                                     abs(np.y - xs[k][np.x].second)) <= t)
          &&
          !(ys[k].count(np.y) && min(abs(np.x - ys[k][np.y].first),
                                     abs(np.x - ys[k][np.y].second)) <= t))
        valid = false;
    }
    if (valid)
      return true;
  }
  return false;
}

bool checkWithAdditionalMid(lli t)
{
  for (int i: components[0])
    for (int j: components[1])
      if (points[i].sameLine(points[j]) && points[i].dist(points[j]) <= 2*t)
        return true;
  return false;
}

bool can(lli t)
{
  for (int i = 0; i < n; i++)
    graph[i].clear();

  for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++)
      if (points[i].sameLine(points[j]) && points[i].dist(points[j]) <= t)
        graph[i].push_back(j), graph[j].push_back(i);

  memset(visited, false, sizeof(visited));
  components.clear();
  xs.clear(), ys.clear();
  for (int i = 0; i < n; i++)
    if (!visited[i])
    {
      components.push_back(vector<int>());
      xs.push_back(unordered_map<lli, pair<lli, lli>>()), ys.push_back(unordered_map<lli, pair<lli, lli>>());
      dfs(i);
    }

  DEBUG printf("\t%lld %d\n", t, (int)xs.size());
  if (xs.size() == 1) return true;
  if (xs.size() == 2) return checkWithAdditionalMid(t) || checkWithAdditional(trialPoints, t);
  if (xs.size() >= 3 && xs.size() <= 4) return checkWithAdditional(trialPoints, t);
  return false;
}
lli binarySearch(lli lo = 0, lli hi = inf)
{
  while (lo < hi)
  {
    lli mid = (lo + hi) >> 1LL;
    if (can(mid)) hi = mid;
    else lo = mid + 1;
  }
  return lo;
}

template<typename T>
void sortUnique(vector<T> &v)
{
  sort(v.begin(), v.end());
  v.resize(distance(v.begin(), unique(v.begin(), v.end())));
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    ux.clear(), uy.clear();
    for (int i = 0; i < n; i++)
    {
      points[i].read();
      ux.push_back(points[i].x), uy.push_back(points[i].y);
    }
    sortUnique(ux), sortUnique(uy);

    trialPoints.clear();
    for (int i = 0; i < ux.size(); i++)
      for (int j = 0; j < uy.size(); j++)
        trialPoints.push_back(Point{ux[i], uy[j]});
    sortUnique(trialPoints);

    lli ans = binarySearch();
    if (ans == inf) ans = -1;
    printf("%lld\n", ans);
  }
  return 0;
}
