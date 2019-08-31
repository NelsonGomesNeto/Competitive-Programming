#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 150, maxV = 2*150 + 2; int n;
const double eps = 1e-7, inf = 1e9;
struct Point
{
  double x, y;
  bool read() { return scanf("%lf %lf", &x, &y); }
  bool operator<(const Point &other) const { return x < other.x || (x == other.x && y < other.y); }
  bool operator==(const Point &other) const { return x == other.x && y == other.y; }
  double dist(Point &other) { return sqrt((x-other.x)*(x-other.x) + (y-other.y)*(y-other.y)); }
  Point operator-(const Point &p) { return Point({x - p.x, y - p.y}); }
  double operator*(const Point &p) { return x * p.x + y * p.y; }
  bool ccw(Point &B, Point &C)
  {
    return (C.y - this->y) * (B.x - this->x) > (B.y - this->y) * (C.x - this->x);
  }
};
struct Segment
{
  Point p1, p2;
  bool read() { p1.read(); return p2.read(); }
  bool interceptsSegment(Point &q1, Point &q2)
  {
    return this->p1.ccw(q1, q2) != p2.ccw(q1, q2) && this->p1.ccw(p2, q1) != this->p1.ccw(p2, q2);
  }
  bool interceptsSegment(Segment &s)
  {
    return this->interceptsSegment(s.p1, s.p2);
  }
};
Segment segments[maxN]; Point origin, destination;

int originId, destinationId;
double dist[maxV];
vector<pair<int, double>> graph[maxN*2 + 2];
Point getPoint(int id)
{
  if (id == originId) return origin;
  if (id == destinationId) return destination;
  return id & 1 ? segments[id >> 1].p2 : segments[id >> 1].p1;
}
void addEdge(int u, int v)
{
  Point a = getPoint(u), b = getPoint(v);
  double d = a.dist(b);
  graph[u].push_back({v, d}), graph[v].push_back({u, d});
}

struct State
{
  int u; double d;
  bool operator<(const State &other) const { return d > other.d; }
};

int main()
{
  while (origin.read() && destination.read() && scanf("%d", &n) && !(!n && !origin.x && !origin.y && !destination.x && !destination.y))
  {
    originId = 2*n, destinationId = 2*n + 1;
    for (int i = 0; i < 2*n + 2; i ++) dist[i] = inf, graph[i].clear();
    for (int i = 0; i < n; i ++) segments[i].read();

    bool valid[4];
    for (int i = 0; i < n; i ++)
    {
      for (int j = i + 1; j < n; j ++)
      {
        valid[0] = valid[1] = valid[2] = valid[3] = true;
        for (int k = 0; k < n && (valid[0] || valid[1] || valid[2] || valid[3]); k ++)
          if (i != k && j != k)
          {
            if (segments[k].interceptsSegment(segments[i].p1, segments[j].p1))
              valid[0] = false;
            if (segments[k].interceptsSegment(segments[i].p1, segments[j].p2))
              valid[1] = false;
            if (segments[k].interceptsSegment(segments[i].p2, segments[j].p1))
              valid[2] = false;
            if (segments[k].interceptsSegment(segments[i].p2, segments[j].p2))
              valid[3] = false;
          }
        if (valid[0]) addEdge(2*i, 2*j);
        if (valid[1]) addEdge(2*i, 2*j + 1);
        if (valid[2]) addEdge(2*i + 1, 2*j);
        if (valid[3]) addEdge(2*i + 1, 2*j + 1);
      }
      valid[0] = valid[1] = valid[2] = valid[3] = true;
      for (int k = 0; k < n && (valid[0] || valid[1] || valid[2] || valid[3]); k ++)
        if (i != k)
        {
          if (segments[k].interceptsSegment(segments[i].p1, origin))
            valid[0] = false;
          if (segments[k].interceptsSegment(segments[i].p2, origin))
            valid[1] = false;
          if (segments[k].interceptsSegment(segments[i].p1, destination))
            valid[2] = false;
          if (segments[k].interceptsSegment(segments[i].p2, destination))
            valid[3] = false;
        }
      if (valid[0]) addEdge(2*i, originId);
      if (valid[1]) addEdge(2*i + 1, originId);
      if (valid[2]) addEdge(2*i, destinationId);
      if (valid[3]) addEdge(2*i + 1, destinationId);
    }
    bool originToDest = true;
    for (int i = 0; i < n; i ++)
      if (segments[i].interceptsSegment(origin, destination))
        originToDest = false;
    if (originToDest) addEdge(originId, destinationId);

    priority_queue<State> pq;
    pq.push({originId, dist[originId] = 0});
    while (!pq.empty())
    {
      int u = pq.top().u; double d = pq.top().d; pq.pop();
      if (dist[u] < d) continue;
      for (auto v: graph[u])
        if (dist[u] + v.second < dist[v.first])
          pq.push({v.first, dist[v.first] = dist[u] + v.second});
    }
    double ans = dist[destinationId];
    printf("%.2lf\n", ans);
  }
  return(0);
}