#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 18, maxM = 100; int n, m;
struct Restriction
{
  int x, y, z;
  void read() { scanf("%d %d %d", &x, &y, &z); x--, y--; }
  bool operator<(const Restriction &other) const { return x < other.x; }
};
Restriction r[maxM];

lli fat[maxN + 1];

int endMask;
lli memo[1 << maxN];
lli solve(int used = 0)
{
  int i = __builtin_popcount(used);
  for (int j = 0; j < m; j++)
    if (r[j].x + 1 == i)
    {
      int cnt = __builtin_popcount(((1 << (r[j].y + 1)) - 1) & used);
      if (cnt > r[j].z)
        return 0;
    }

  if (i == n)
    return 1;

  lli &ans = memo[used];
  if (ans != -1)
    return ans;

  ans = 0;
  int unused = ~used;
  for (int j = 0; j < n; j++)
    if (unused & (1 << j))
      ans += solve(used | (1 << j));

  return ans;
}

int main()
{
  fat[0] = 1;
  for (int i = 1; i <= maxN; i++)
    fat[i] = fat[i - 1] * i;

  while (~scanf("%d %d", &n, &m))
  {
    endMask = (1 << (n + 1)) - 1;

    for (int i = 0; i < m; i++)
      r[i].read();

    memset(memo, -1, sizeof(memo));
    lli ans = solve();
    printf("%lld\n", ans);
  }
  return 0;
}