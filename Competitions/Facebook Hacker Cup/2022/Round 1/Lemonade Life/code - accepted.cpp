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
vector<Point> paths[2]; // 0 - below, 1 - above;
vector<Point> goodHouses;

lli getCost(const Point& a, const Point &b)
{
  return max(k, a.squaredDistance(b));
}
bool reachable(const Point& a, const Point &b)
{
  return a.squaredDistance(b) <= dd;
}

lli memo[maxN];
lli solve(int i = 0)
{
  if (i == goodHouses.size() - 1)
    return 0;

  lli &ans = memo[i];
  if (ans != -1) return ans;

  ans = inf;
  for (int j = i + 1; j < goodHouses.size(); ++j)
    if (reachable(goodHouses[i], goodHouses[j]))
    {
      lli futureCost = solve(j);
      if (futureCost == inf) continue;
      ans = min(ans, getCost(goodHouses[i], goodHouses[j]) + futureCost);
    }

  return ans;
}

Point firstHouse, lastHouse;
// y = m*x + b
struct Line
{
  // lli m, b;
  Point m; lli b;
  lli value(const Point& x)
  {
    if (reachable(m, x))
      return getCost(m, x) + b;
    else
      return inf;
  }
};
struct LiChaoTree2D
{
  int sizeX, sizeY;
  vector<unordered_map<int, Line>> lines;
  Line nilLine;
  LiChaoTree2D() { }
  LiChaoTree2D(int sizeX, int sizeY) : sizeX(sizeX), sizeY(sizeY)
  {
    nilLine = {Point{0, 0}, 0};
    lines.resize(4*sizeX);
  }
  void addLine(Line newLine) { addLine(newLine, 1, 0, sizeX); }
  void addLineVertical(Line& newLine, int x, int lox, int hix, int y, int loy, int hiy)
  {
    int midy = (loy + hiy) >> 1;
    bool leftEval = !lines[x].count(y) || newLine.value(Point{newLine.m.x, loy}) < getValue(Point{newLine.m.x, loy}, x, y);
    bool midEval = !lines[x].count(y) || newLine.value(Point{newLine.m.x, midy}) < getValue(Point{newLine.m.x, midy}, x, y);
    if (midEval)
      lines[x][y] = newLine;

    if (loy == hiy - 1) return;
    if (newLine.m.y <= midy) addLineVertical(newLine, x, lox, hix, 2*y, loy, midy);
    if (newLine.m.y >= midy) addLineVertical(newLine, x, lox, hix, 2*y + 1, midy, hiy);
  }
  void addLine(Line &newLine, int x, int lox, int hix)
  {
    int midx = (lox + hix) >> 1;
    if (lox == hix - 1)
    {
      addLineVertical(newLine, x, lox, hix, 1, 0, sizeY);
      return;
    }
    if (newLine.m.x <= midx) addLine(newLine, 2*x, lox, midx);
    if (newLine.m.x >= midx) addLine(newLine, 2*x + 1, midx, hix);
    addLineVertical(newLine, x, lox, hix, 1, 0, sizeY);
  }
  lli get(const Point& p) { return get(p, 1, 0, sizeX); }
  lli getValue(const Point& p, int x, int y)
  {
    return lines[x].count(y) ? lines[x][y].value(p) : inf;
  }
  lli getVertical(const Point& p, int x, int lox, int hix, int y, int loy, int hiy)
  {
    if (loy == hiy - 1) return getValue(p, x, y);
    int midy = (loy + hiy) >> 1;
    lli best = inf;
    if (p.y <= midy) best = min(getValue(p, x, y), getVertical(p, x, lox, hix, 2*y, loy, midy));
    if (p.y >= midy) best = min({best, getValue(p, x, y), getVertical(p, x, lox, hix, 2*y + 1, midy, hiy)});
    return best;
  }
  lli get(const Point& p, int x, int lox, int hix)
  {
    if (lox == hix - 1) return getVertical(p, x, lox, hix, 1, 0, sizeY);
    int midx = (lox + hix) >> 1;
    lli best = inf;
    if (p.x <= midx) best = min(getVertical(p, x, lox, hix, 1, 0, sizeY), get(p, 2*x, lox, midx));
    if (p.x >= midx) best = min({best, getVertical(p, x, lox, hix, 1, 0, sizeY), get(p, 2*x + 1, midx, hix)});
    return best;
  }
};
LiChaoTree2D liChaoTree;

lli solve2()
{
  fill(memo, memo + goodHouses.size(), inf);
  memo[0] = 0;
  liChaoTree = LiChaoTree2D(goodHouses.back().x + 1, (int)1e6 + 1);
  liChaoTree.addLine(Line{goodHouses[0], memo[0]});

  for (int i = 1; i < goodHouses.size(); ++i)
  {
    // memo[i] = liChaoTree.get(goodHouses[i]);
    for (int k = 1; k <= 10; ++k)
      if (i - k >= 0 && memo[i - k] != inf && reachable(goodHouses[i], goodHouses[i - k]))
        memo[i] = min(memo[i], getCost(goodHouses[i], goodHouses[i - k]) + memo[i - k]);
    if (memo[i] == inf) continue;
    // liChaoTree.addLine(Line{goodHouses[i], memo[i]});
    if (goodHouses[i].index == n - 1)
      return memo[i];
  }

  DEBUG {
    printf("\t");
    for (int i = 0; i < goodHouses.size(); ++i)
      printf("%lld%c", memo[i], i + 1 < goodHouses.size() ? ' ' : '\n');
  }

  return memo[goodHouses.size() - 1];
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
    firstHouse = houses[0];
    lastHouse = houses[n - 1];
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

    goodHouses.clear();
    goodHouses.push_back(paths[0][0]);
    for (int isAbove = 0; isAbove < 2; ++isAbove)
      for (int i = 1; i < paths[isAbove].size() - 1; ++i)
        goodHouses.push_back(paths[isAbove][i]);
    goodHouses.push_back(paths[0].back());
    sort(goodHouses.begin(), goodHouses.end(), [](const Point& a, const Point& b) {
      return a.x < b.x || (a.x == b.x && a.y < b.y);
    });

    DEBUG {
      printf("\tAbove:\n");
      for (Point& p : paths[1]) p.print();
      printf("\tBelow:\n");
      for (Point& p : paths[0]) p.print();
    }

    // fill(memo, memo + goodHouses.size(), -1);
    // lli ans = solve();

    lli ans = solve2();
    sort(goodHouses.begin(), goodHouses.end(), [](const Point& a, const Point& b) {
      return firstHouse.squaredDistance(a) < firstHouse.squaredDistance(b);
    });
    ans = min(ans, solve2());
    if (ans == inf) ans = -1;
    printf("Case #%d: %lld\n", testCase, ans);
  }
  return 0;
}
