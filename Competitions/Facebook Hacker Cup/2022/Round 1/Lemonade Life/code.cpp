#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const lli inf = LONG_LONG_MAX;

void fastReadInt(lli &x)
{
  bool neg = false;
  int c = ' ';
  x = 0;
  while (c != '-' && (c < '0' || c > '9'))
    c = getchar();
 
  if (c == '-')
    neg = true, c = getchar();
 
  for ( ; (c > 47 && c < 58); c = getchar())
    x = (x<<1) + (x<<3) + c - 48;
  if (neg)
    x *=-1;
}

struct Point
{
  lli x, y; int index;
  void read() { fastReadInt(x); fastReadInt(y); }
  void print(string prefix = "", string suffix = "\n") const { printf("%s(%4lld, %4lld)%s", prefix.c_str(), x, y, suffix.c_str()); }
  double crossProduct(const Point& other) const { return x*other.y - y*other.x; }
  int orientation(const Point& b, const Point& c) const
  {
    lli sa = signedArea(b, c);
    if (sa < 0) return -1; // clockwise;
    else if (sa > 0) return 1; // counter-clockwise
    return 0; // collinear
  }
  lli signedArea(const Point& b, const Point& c) const { return x*(b.y - c.y) + b.x*(c.y - y) + c.x*(y - b.y); }
  lli squaredDistance(const Point& other) const { return (x - other.x)*(x - other.x) + (y - other.y)*(y - other.y); }
};

vector<Point> convexHull(vector<Point> &points, bool includeCollinear = false)
{
  // Left-bottom most;
  Point p0 = *min_element(points.begin(), points.end(), [](const Point& a, const Point& b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
  });
  sort(points.begin(), points.end(), [&p0](const Point& a, const Point& b) {
    int o = p0.orientation(a, b);
    if (o == 0) return p0.squaredDistance(a) < p0.squaredDistance(b);
    return o < 0;
  });

  vector<Point> ans;
  int allowedOrientation = includeCollinear ? 0 : -1;
  for (int i = 0; i < points.size(); i++)
  {
    while (ans.size() >= 2 && ans[ans.size() - 2].orientation(ans.back(), points[i]) > allowedOrientation)
      ans.pop_back();
    ans.push_back(points[i]);
  }

  return ans;
}

const int maxN = 1e6; int n; lli k, d, dd;
vector<Point> houses;
vector<Point> goodHouses;

lli getCost(const Point& a, const Point &b)
{
  return max(k, a.squaredDistance(b));
}
bool reachable(const Point& a, const Point &b)
{
  return a.squaredDistance(b) <= dd;
}

lli cost[maxN];
bool inqueue[maxN];
lli dijkstra()
{
  fill(cost, cost + goodHouses.size(), inf);
  fill(inqueue, inqueue + goodHouses.size(), false);
  deque<int> q;
  q.push_back(0), cost[0] = 0, inqueue[0] = true;
  while (!q.empty())
  {
    auto best = min_element(q.begin(), q.end(), [](const int& a, const int& b) {
      return cost[a] < cost[b];
    });
    int i = *best;
    q.erase(best), inqueue[i] = false;

    for (int j = 0; j < goodHouses.size(); ++j)
    {
      lli dist = goodHouses[i].squaredDistance(goodHouses[j]);
      if (dist > dd) continue;
      lli newCost = cost[i] + max(k, dist);
      if (newCost < cost[j])
      {
        if (!inqueue[j]) q.push_back(j), inqueue[j] = true;
        cost[j] = newCost;
      }
    }
  }
  return cost[max_element(goodHouses.begin(), goodHouses.end(), [](const Point& a, const Point& b) {
    return a.x > b.x;
  }) - goodHouses.begin()];
}

int main()
{
  int testCases; scanf("%d", &testCases);
  for (int testCase = 1; testCase <= testCases; ++testCase)
  {
    scanf("%d %lld %lld", &n, &k, &d);
    dd = d*d;
    houses.clear();
    houses.resize(n);
    for (int i = 0; i < n; ++i)
    {
      houses[i].read();
      houses[i].index = i;
    }

    goodHouses = convexHull(houses, false);
    // sort(goodHouses.begin(), goodHouses.end(), [](const Point& a, const Point& b) {
    //   return a.x < b.x || (a.x == b.x && a.y < b.y);
    // });

    lli ans = dijkstra();
    if (ans == inf) ans = -1;
    printf("Case #%d: %lld\n", testCase, ans);
  }
  return 0;
}
