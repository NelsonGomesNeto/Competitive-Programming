#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3; int x, y, n;
const ldouble eps = 1e-12;
struct Point
{
  ldouble x, y;
  void read() { scanf("%Lf %Lf", &x, &y); }
  ldouble distance(Point &other) { return sqrt((x - other.x)*(x - other.x) + (y - other.y)*(y - other.y)); }
};
Point points[maxN], origin, destination;

// n - left, n + 1 right, n + 2 top, n + 3 down
int LEFT, RIGHT, TOP, DOWN;
const int maxV = maxN + 4; int vertices;
vector<int> graph[maxV];
bool visited[maxV];
void bfs(int source)
{
  memset(visited, false, sizeof(visited));
  queue<int> q; q.push(source);
  while (!q.empty())
  {
    int u = q.front(); q.pop();
    if (visited[u]) continue;
    visited[u] = true;
    for (int v: graph[u])
      q.push(v);
  }
}
void addEdge(int u, int v)
{
  graph[u].push_back(v), graph[v].push_back(u);
}
bool equal(ldouble a, ldouble b)
{
  return abs(a - b) < eps;
}
bool can(ldouble r)
{
  for (int i = 0; i < vertices; i++)
    graph[i].clear();

  for (int i = 0; i < n; i++)
  {
    if (points[i].distance(origin) <= r || equal(points[i].distance(origin), r)) return false;
    if (points[i].distance(destination) <= r || equal(points[i].distance(destination), r)) return false;
    if (points[i].x <= r || equal(points[i].x, r)) addEdge(LEFT, i);
    if (points[i].y <= r || equal(points[i].x, r)) addEdge(DOWN, i);
    if (x - points[i].x <= r || equal(x - points[i].x, r)) addEdge(RIGHT, i);
    if (y - points[i].y <= r || equal(y - points[i].y, r)) addEdge(TOP, i);

    for (int j = i + 1; j < n; j++)
      if (points[i].distance(points[j]) <= 2*r || equal(points[i].distance(points[j]), 2*r))
        addEdge(i, j);
  }

  bfs(LEFT);
  DEBUG printf("\t\t%Lf - %d %d %d %d\n", r, visited[LEFT], visited[TOP], visited[RIGHT], visited[DOWN]);
  if (visited[RIGHT] || visited[DOWN])
    return false;
  bfs(TOP);
  DEBUG printf("\t\t%Lf - %d %d %d %d\n", r, visited[LEFT], visited[TOP], visited[RIGHT], visited[DOWN]);
  if (visited[RIGHT] || visited[DOWN])
    return false;

  return true;
}

int main()
{
  while (~scanf("%d %d %d", &x, &y, &n))
  {
    LEFT = n, RIGHT = n + 1, TOP = n + 2, DOWN = n + 3;
    vertices = n + 4;
    origin = Point{0, 0}, destination = Point{(ldouble)x, (ldouble)y};

    for (int i = 0; i < n; i++)
      points[i].read();

    ldouble lo = 0, hi = min(x, y);
    while (abs(hi - lo) > eps)
    {
      ldouble mid = (lo + hi) / 2;
      bool res = can(mid);
      DEBUG printf("\t%Lf %d\n", mid, res);
      if (res) lo = mid;
      else hi = mid;
    }

    printf("%.15Lf\n", hi);
  }
  return 0;
}