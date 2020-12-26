#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 12, maxM = 1e3; int n, m;
const lli inf = 1e15;
struct Key
{
  lli a; int b, canUnlock;
  void read()
  {
    scanf("%lld %d", &a, &b);
    canUnlock = 0;
    for (int i = 0; i < b; i ++)
    {
      int c; scanf("%d", &c); c --;
      canUnlock |= 1 << c;
    }
  };
};
Key keys[maxM];

lli memo[maxM][1 << maxN];
lli solve(int i = 0, int done = 0)
{
  if (done == (1 << n) - 1) return 0;
  if (i == m) return inf;
  if (memo[i][done] == -1)
  {
    lli ans = min(solve(i + 1, done), solve(i + 1, done | keys[i].canUnlock) + keys[i].a);
    memo[i][done] = ans;
  }
  return memo[i][done];
}

int main()
{
  scanf("%d %d", &n, &m);
  for (int i = 0; i < m; i ++)
    keys[i].read();

  memset(memo, -1, sizeof(memo));
  lli ans = solve();
  printf("%lld\n", ans >= inf ? -1 : ans);

  return 0;
}