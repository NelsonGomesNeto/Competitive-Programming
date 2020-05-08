#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

char dir[5] = "NSEW";
int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
const int maxPot = 40, maxIt = 1e5;
lli pot[maxPot];

lli sx, sy;

struct Pos
{
  lli x, y, d;
  Pos(lli x, lli y) : x(x), y(y)
  {
    d = abs(x - sx) + abs(y - sy);
  }
  Pos operator+(const Pos &other)
  {
    return Pos{x + other.x, y + other.y};
  }
  bool operator<(const Pos &other) const
  {
    return x < other.x || (x == other.x && y < other.y);
  }
};
struct Node
{
  int i; Pos pos; string path;
  bool operator<(const Node &other) const
  {
    return i > other.i || (i == other.i && pos.d > other.pos.d);
  };
};
bool possible(lli a, lli b, int i)
{
  return (abs(a - b) & ((1 << i) - 1)) == 0;
}
string ans;
bool solve(Node u)
{
  if (u.i == maxPot) return false;
  if (u.pos.x == sx && u.pos.y == sy)
  {
    if (ans.empty() || u.path.size() < ans.size())
      ans = u.path;
    return true;
  }
  for (int k = 0; k < 4; k++)
  {
    Node v = Node{u.i + 1, u.pos + Pos{pot[u.i] * dx[k], pot[u.i] * dy[k]}};
    if (possible(v.pos.x, sx, u.i + 1) && possible(v.pos.y, sy, u.i + 1))
    {
      v.path = u.path + dir[k];
      solve(v);
    }
  }
  return false;
}

int main()
{
  pot[0] = 1;
  for (int i = 1; i < maxPot; i++) pot[i] = 2LL * pot[i - 1];

  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%lld %lld", &sx, &sy);
    ans.clear();
    solve(Node{0, {0, 0}});
    if (ans.empty()) ans = "IMPOSSIBLE";
    printf("Case #%d: %s\n", tt, ans.c_str());
  }
  return 0;
}