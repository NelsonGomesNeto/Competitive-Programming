#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3, maxX = 1e4; int n;
int a[maxN];
int acc[maxN + 1];

struct Point
{
  int x, y;
  void read() { scanf("%d %d", &x, &y); }
  bool operator==(const Point& other) const { return x == other.x && y == other.y; }
  int manhattanDistance(const Point &other) const { return abs(x - other.x) + abs(y - other.y); }
};
Point target;
int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};

unordered_set<int> memo[maxN];
bool solve(int i = 1, Point pos = {a[0], 0})
{
  if (i == n) return pos == target;
  if (acc[n] - acc[i] < pos.manhattanDistance(target)) return false;
  if (memo[0].count(pos.x * maxX + pos.y)) return false;

  for (int d = i & 1; d < 4; d += 2)
    if (solve(i + 1, {pos.x + dx[d]*a[i], pos.y + dy[d]*a[i]}))
      return true;

  memo[0].insert(pos.x * maxX + pos.y);
  return false;
}

int main()
{
  while (~scanf("%d %d %d", &n, &target.x, &target.y))
  {
    for (int i = 0; i < n; ++i)
      scanf("%d", &a[i]);
    for (int i = 0; i < n; ++i)
      acc[i + 1] = acc[i] + a[i];

    for (int i = 0; i < n; ++i)
      memo[i].clear();

    bool can = solve();
    printf("%s\n", can ? "Yes" : "No");
  }
  return 0;
}
