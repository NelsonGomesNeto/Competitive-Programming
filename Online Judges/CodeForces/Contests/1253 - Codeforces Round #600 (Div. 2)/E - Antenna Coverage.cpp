#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 80, maxM = 1e5 + 1; int n, m;
struct Antenna
{
  int x, s;
  void read() { scanf("%d %d", &x, &s); }
};
Antenna a[maxN];

int memo[maxM];
int solve(int i = 1)
{
  if (i > m) return 0;
  if (memo[i] != -1) return memo[i];

  int ans = m;
  for (int j = 0; j < n; j ++)
  {
    int toAdd = i <= a[j].x - a[j].s ? a[j].x - a[j].s - i : 0;
    if (a[j].x - a[j].s <= i && a[j].x + a[j].s >= i)
      ans = min(ans, solve(a[j].x + a[j].s + 1));
    if (i <= a[j].x)
      ans = min(ans, solve(a[j].x + a[j].s + toAdd + 1) + toAdd);
    ans = min(ans, max(toAdd, m - (a[j].x + a[j].s)));
  }
  return memo[i] = ans;
}

int main()
{
  while (scanf("%d %d", &n, &m) != EOF)
  {
    for (int i = 0; i < n; i ++)
      a[i].read();

    memset(memo, -1, sizeof(memo));
    int ans = solve();
    printf("%d\n", ans);
  }
  return 0;
}
