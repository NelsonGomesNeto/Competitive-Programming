#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3, maxX = 1e4; int n;
int a[maxN];

struct Point
{
  int x, y;
  void read() { scanf("%d %d", &x, &y); }
  bool operator==(const Point& other) const { return x == other.x && y == other.y; }
};
int targetX, targetY, target;

short memo[maxN][2*maxX + 1];
bool solve(int i, int pos)
{
  if (i >= n) return pos == target;
  short& can = memo[i][pos];
  if (can != -1) return can;
  return can = solve(i + 2, pos + a[i]) || solve(i + 2, pos - a[i]);
}

int main()
{
  while (~scanf("%d %d %d", &n, &targetX, &targetY))
  {
    for (int i = 0; i < n; ++i)
      scanf("%d", &a[i]);

    memset(memo, -1, sizeof(memo));
    target = targetX;
    bool canX = solve(2, a[0]);
    target = targetY;
    bool canY = solve(1, 0);
    bool can = canX && canY;
    printf("%s\n", can ? "Yes" : "No");
  }
  return 0;
}
