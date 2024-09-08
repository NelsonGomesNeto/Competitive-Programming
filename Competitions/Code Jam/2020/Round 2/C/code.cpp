#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
for each point p:
  normalize all points such that p is the center
  sort them counter-clockwise
  count the number of points that align (has angle equal or exactly 180 apart)

  it will be better if we use dy / dx (and angle dx = 0 cases)
  this way we can use fraction :)
*/

lli lcm(lli a, lli b)
{
  return a / __gcd(a, b) * b;
}

const int maxN = 100; int n;
struct Point
{
  lli x, y;
  void read() { scanf("%lld %lld", &x, &y); }
  double dist(Point &other)
  {
    return sqrt((x - other.x)*(x - other.x) + (y - other.y)*(y - other.y));
  }
};
struct fraction
{
  lli numerator, divisor; bool neg = false;
  double angle;
  fraction(lli numerator, lli divisor)
  {
    lli g = __gcd(numerator, divisor);
    this->numerator = numerator / g;
    this->divisor = divisor / g;
    neg = this->divisor < 0;
  }
  bool operator<(const fraction &other) const
  {
    // be very careful not to overflow here
    lli l = lcm(divisor, other.divisor);
    return numerator * (l / divisor) < other.numerator * (l / other.divisor);
  }
  bool operator==(const fraction &other) const
  {
    // return angle == other.angle;
    return numerator == other.numerator && divisor == other.divisor && neg == other.neg;
  }
};
Point points[maxN];

int visited[maxN];
int dfs(int u, int prv = -10, bool teleported = false, bool hasDirection = false, double angle = 0, bool first = true, int depth = 0)
{
  DEBUG {
    for (int hehe = 0; hehe < depth; hehe++) printf("   ");
    printf("%d |%d| (%d)\n", u + 1, teleported, depth);
  }

  int aa = visited[u] == -1;
  visited[u] = prv;

  int ans = 0;
  for (int v = 0; v < n; v++)
    if (1)
    {
      double currAngle = atan2(points[v].y - points[u].y, points[v].x - points[u].x);
      if ((!teleported || first) && (visited[v] == -1 || visited[u] == v))
        ans = max(ans, dfs(v, true, hasDirection, angle, false, depth + 1));
      if ((teleported || first) && (!hasDirection || abs(angle - currAngle) <= 1e-6))
        ans = max(ans, dfs(v, false, true, currAngle, false, depth + 1));
    }

  visited[u];

  return aa + ans;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
      points[i].read();

    int ans = 1;
    for (int i = 0; i < n; i++)
    {
      memset(visited, -1, sizeof(visited));
      ans = max(ans, dfs(i));
    }
    printf("Case #%d: %d\n", tt, ans);
  }
  return 0;
}