#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

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
const lli inf = LONG_LONG_MAX;
Point destination;
vector<Point> houses;
vector<Point> paths[2]; // 0 - below, 1 - above;
int otherSideClosest[2][maxN];

lli getCost(const Point& a, const Point &b)
{
  return max(k, a.squaredDistance(b));
}

bool squaredDistanceSmallerThanDD(const Point& a, const Point& b)
{
  return a.squaredDistance(b) <= dd;
}
bool squaredDistanceSmallerThanK(const Point& a, const Point& b)
{
  return a.squaredDistance(b) <= min(k, dd);
}
bool squaredDistanceGreaterThanK(const Point& a, const Point& b)
{
  lli dist = a.squaredDistance(b);
  return dist >= k && dist <= dd;
}

// Finds the furthest point subject to a limiting function.
int binarySearch(const Point& at, bool searchAbove, function<bool(const Point&, const Point&)> isWithinLimit, int lo, int hi, bool isUpperBound)
{
  while (lo < hi)
  {
    int mid = (lo + hi + isUpperBound) >> 1;
    if (isUpperBound)
    {
      if (isWithinLimit(at, paths[searchAbove][mid])) lo = mid;
      else hi = mid - 1;
    }
    else
    {
      if (isWithinLimit(at, paths[searchAbove][mid])) hi = mid;
      else lo = mid + 1;
    }
  }
  return isWithinLimit(at, paths[searchAbove][lo]) ? lo : -1;
}
int binarySearch(const Point& at, bool searchAbove, int lo, function<bool(const Point&, const Point&)> isWithinLimit, bool isUpperBound)
{
  return binarySearch(at, searchAbove, isWithinLimit, lo, paths[searchAbove].size() - 1, isUpperBound);
}
double eval(const Point& a, const Point& b)
{
  return (double)destination.squaredDistance(b) / getCost(a, b);
}
int ternarySearch(const Point& at, bool searchAbove, int lo, int hi)
{
  while (lo + 3 < hi)
  {
    int midlo = (2*lo + hi) / 3, midhi = (lo + 2*hi + 2) / 3;
    double elo = eval(at, paths[searchAbove][midlo]), ehi = eval(at, paths[searchAbove][midhi]);
    if (elo > ehi) hi = midhi;
    else lo = midlo;
  }
  int bestI; lli bestE = inf;
  for (int i = lo; i <= hi; ++i)
  {
    lli e = eval(at, paths[searchAbove][i]);
    if (e < bestE) bestE = e, bestI = i;
  }
  return bestI;
}

struct State
{
  bool isAbove; int i; lli d;
  bool operator<(const State& other) const { return d > other.d; }
};
lli costs[2][maxN];
State prv[2][maxN];
lli dijkstra()
{
  fill(costs[0], costs[0] + paths[0].size(), inf);
  fill(costs[1], costs[1] + paths[1].size(), inf);
  priority_queue<State> pq;
  pq.push(State{false, 0, costs[false][0] = 0});
  pq.push(State{true, 0, costs[true][0] = 0});
  while (!pq.empty())
  {
    State now = pq.top();
    pq.pop();
    if (now.d > costs[now.isAbove][now.i]) continue;
    const Point& nowAt = paths[now.isAbove][now.i];

    // ------------- Naive Brute Search

    bool newIsAbove = now.isAbove;
    for (int i = 0; i < 2; ++i)
    {
      for (int j = 0; j < paths[newIsAbove].size(); ++j)
      {
        if (!squaredDistanceSmallerThanDD(nowAt, paths[newIsAbove][j]))
          continue;
        lli newCost = now.d + getCost(nowAt, paths[newIsAbove][j]);
        if (newCost < costs[newIsAbove][j])
        {
          prv[newIsAbove][j] = now;
          pq.push(State{newIsAbove, j, costs[newIsAbove][j] = newCost});
        }
      }
      newIsAbove = 1-newIsAbove;
    }

    // ------------ Smart Ternary Search

    // bool newIsAbove = now.isAbove;
    // int lo = now.i + 1;
    // for (int i = 0; i < 2; ++i)
    // {
    //   if (lo >= paths[newIsAbove].size()) continue;
    //   int newI = binarySearch(nowAt, newIsAbove, lo, squaredDistanceSmallerThanK);
    //   if (newI == -1) newI = lo;

    //   newI = ternarySearch(nowAt, newIsAbove, lo, newI);
    //   lli newCost = now.d + getCost(nowAt, paths[newIsAbove][newI]);
    //   if (newCost < costs[newIsAbove][newI])
    //     pq.push(State{newIsAbove, newI, costs[newIsAbove][newI] = newCost});

    //   newIsAbove = !newIsAbove;
    //   lo = otherSideClosest[now.isAbove][now.i];
    // }

    // newIsAbove = now.isAbove;
    // lo = now.i + 1;
    // for (int i = 0; i < 2; ++i)
    // {
    //   if (lo >= paths[newIsAbove].size()) continue;
    //   int lolo = lo;
    //   lo = binarySearch(nowAt, newIsAbove, lo, squaredDistanceGreaterThanK, false);
    //   int newI = binarySearch(nowAt, newIsAbove, lo, squaredDistanceSmallerThanDD, true);
    //   if (lo == -1) lo = lolo;
    //   if (newI == -1) newI = lo;
    //   if (lo > newI) continue;

    //   newI = ternarySearch(nowAt, newIsAbove, lo, newI);
    //   lli newCost = now.d + getCost(nowAt, paths[newIsAbove][newI]);
    //   if (newCost < costs[newIsAbove][newI])
    //     pq.push(State{newIsAbove, newI, costs[newIsAbove][newI] = newCost});

    //   newIsAbove = !newIsAbove;
    //   lo = otherSideClosest[now.isAbove][now.i];
    // }

    // --------------- Smart Binary Search

    // // Search on my side
    // bool newIsAbove = now.isAbove;
    // for (auto& [eval, isUpperBound] : {make_pair(squaredDistanceSmallerThanDD, true), make_pair(squaredDistanceSmallerThanK, true), make_pair(squaredDistanceGreaterThanK, false)})
    // {
    //   int newI = binarySearch(nowAt, newIsAbove, now.i, eval, isUpperBound);
    //   if (newI == -1 || newI == now.i) continue;
    //   lli newCost = now.d + getCost(nowAt, paths[newIsAbove][newI]);
    //   if (newCost < costs[newIsAbove][newI])
    //   {
    //     prv[newIsAbove][newI] = now;
    //     pq.push(State{newIsAbove, newI, costs[newIsAbove][newI] = newCost});
    //   }
    // }
    // // Simply use the next on my side
    // int newI = now.i + 1;
    // if (newI < paths[newIsAbove].size() && squaredDistanceSmallerThanDD(nowAt, paths[newIsAbove][newI]))
    // {
    //   lli newCost = now.d + getCost(nowAt, paths[newIsAbove][newI]);
    //   if (newCost < costs[newIsAbove][newI])
    //   {
    //     prv[newIsAbove][newI] = now;
    //     pq.push(State{newIsAbove, newI, costs[newIsAbove][newI] = newCost});
    //   }
    // }

    // // // Search on the other side
    // newIsAbove = !now.isAbove;
    // for (auto& [eval, isUpperBound] : {make_pair(squaredDistanceSmallerThanDD, true), make_pair(squaredDistanceSmallerThanK, true), make_pair(squaredDistanceGreaterThanK, false)})
    // {
    //   int newI = binarySearch(nowAt, newIsAbove, now.i, eval, isUpperBound);
    //   if (newI == -1) continue;
    //   lli newCost = now.d + getCost(nowAt, paths[newIsAbove][newI]);
    //   if (newCost < costs[newIsAbove][newI])
    //   {
    //     prv[newIsAbove][newI] = now;
    //     pq.push(State{newIsAbove, newI, costs[newIsAbove][newI] = newCost});
    //   }
    // }
    // // // Simply use the next on the other side
    // newI = otherSideClosest[now.isAbove][now.i] + 1;
    // if (newI < paths[newIsAbove].size() && squaredDistanceSmallerThanDD(nowAt, paths[newIsAbove][newI]))
    // {
    //   lli newCost = now.d + getCost(nowAt, paths[newIsAbove][newI]);
    //   if (newCost < costs[newIsAbove][newI])
    //   {
    //     prv[newIsAbove][newI] = now;
    //     pq.push(State{newIsAbove, newI, costs[newIsAbove][newI] = newCost});
    //   }
    // }
  }
  return min(costs[0][paths[0].size() - 1], costs[1][paths[1].size() - 1]);
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
    destination = houses[n - 1];
    houses = convexHull(houses, false);

    paths[0].clear();
    paths[0].push_back(houses[0]);
    for (int i = houses.size() - 1; i >= 0; --i)
    {
      paths[0].push_back(houses[i]);
      if (houses[i].index == n - 1)
        break;
    }
    paths[1].clear();
    paths[1].push_back(houses[0]);
    for (int i = 1; i < houses.size(); ++i)
    {
      paths[1].push_back(houses[i]);
      if (houses[i].index == n - 1)
        break;
    }

    for (int j = 0; j < 2; ++j)
    {
      for (int i[2] = {0, 0}; i[j] < paths[j].size(); ++i[j])
      {
        while (i[j] < paths[j].size() && i[1 - j] + 1 < paths[1 - j].size() && paths[1 - j][i[1 - j] + 1].x <= paths[j][i[j]].x)
          ++i[1 - j];
        otherSideClosest[j][i[j]] = i[1 - j];
      }
      for (int i = 0; i < paths[j].size(); ++i)
      {
        // printf("%d %d | %lld %lld | %d\n", j, i, paths[j][i].x, paths[1 - j][otherSideClosest[j][i]].x, otherSideClosest[j][i]);
        assert(paths[j][i].x >= paths[1 - j][otherSideClosest[j][i]].x);
      }
    }

    DEBUG {
      printf("\tAbove:\n");
      for (Point& p : paths[1]) p.print();
      printf("\tBelow:\n");
      for (Point& p : paths[0]) p.print();
    }

    lli ans = dijkstra();
    if (ans == inf) ans = -1;

    DEBUG {
      printf("\tPath below: %lld\n", costs[0][paths[0].size() - 1]);
      State now = {false, (int)paths[0].size() - 1};
      while (now.i != 0)
      {
        printf("\t\t%s %d\n", now.isAbove ? "above" : "below", now.i);
        now = prv[now.isAbove][now.i];
      }
      printf("\tPath above: %lld\n", costs[1][paths[1].size() - 1]);
      now = {true, (int)paths[1].size() - 1};
      while (now.i != 0)
      {
        printf("\t\t%s %d\n", now.isAbove ? "above" : "below", now.i);
        now = prv[now.isAbove][now.i];
      }
    }

    printf("Case #%d: %lld\n", testCase, ans);
  }
  return 0;
}
