#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100 + 1, inf = 1e6; int n;
bool removed[maxN];
int p[maxN], even, odd;

int memo[maxN][maxN][2];
int solve(int i = 0, int e = even, int o = odd, bool prvIsEven = false)
{
  if (i == n) return 0;
  if (memo[i][e][prvIsEven] != -1) return memo[i][e][prvIsEven];
  int ans = inf;
  if (p[i] == 0)
  {
    if (e)
      ans = solve(i + 1, e - 1, o, true) + (i && !prvIsEven);
    if (o)
      ans = min(ans, solve(i + 1, e, o - 1, false) + (i && prvIsEven));
  }
  else
    ans = solve(i + 1, e, o, !(p[i] & 1)) + (i && prvIsEven == (bool) (p[i] & 1));
  return memo[i][e][prvIsEven] = ans;
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 1; i <= n; i ++)
      removed[i] = true;
    even = odd = 0;

    for (int i = 0; i < n; i ++)
    {
      scanf("%d", &p[i]);
      removed[p[i]] = false;
    }
    for (int i = 1; i <= n; i ++)
      if (removed[i])
        even += !(i & 1), odd += i & 1;

    memset(memo, -1, sizeof(memo));
    int ans = solve();
    printf("%d\n", ans);
  }
  return 0;
}
