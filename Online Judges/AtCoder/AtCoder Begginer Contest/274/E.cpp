#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

struct Point
{
  ldouble x, y;
  void read() { scanf("%Lf %Lf", &x, &y); }
  ldouble distance(const Point& other) const
  {
    return sqrtl((x - other.x)*(x - other.x) + (y - other.y)*(y - other.y));
  }
};

struct Town
{
  Point p;
  ldouble distance(const Town& other) const { return p.distance(other.p); }
};

const int maxN = 18; int t, n, m;
const int origin = maxN - 1;
const ldouble inf = numeric_limits<ldouble>::infinity();
Town towns[maxN];

bool visitedAll(int mask)
{
  return (~mask & ((1 << n) - 1)) == 0;
}
ldouble calcSpeed(int mask)
{
  return 1 << __builtin_popcount(mask >> n);
}

ldouble memo[maxN][1 << (maxN - 1)];
ldouble solve(int i = origin, int mask = 0)
{
  if (i == origin && visitedAll(mask)) return 0;
  ldouble &ans = memo[i][mask];
  if (ans != -1) return ans;

  ldouble currentSpeed = calcSpeed(mask);
  ans = inf;
  for (int j = 0; j < t; ++j)
    if ((mask & (1 << j)) == 0)
      ans = min(ans, solve(j, mask | (1 << j)) + towns[i].distance(towns[j]) / currentSpeed);
  if (visitedAll(mask))
    ans = min(ans, solve(origin, mask) + towns[i].distance(towns[origin]) / currentSpeed);
  return ans;
}

int main()
{
  towns[origin] = {{0, 0}};
  while (~scanf("%d %d", &n, &m))
  {
    t = n + m;
    for (int i = 0; i < n; ++i)
      towns[i].p.read();
    for (int i = 0; i < m; ++i)
      towns[n + i].p.read();

    fill(memo[origin], memo[origin]+(1 << t), -1);
    for (int i = 0; i < t; ++i)
      fill(memo[i], memo[i]+(1 << t), -1);
    ldouble ans = solve();
    printf("%.15Lf\n", ans);
  }
  return 0;
}
