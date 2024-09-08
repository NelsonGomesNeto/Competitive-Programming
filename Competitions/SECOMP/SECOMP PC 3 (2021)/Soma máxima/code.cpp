#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
lli a[maxN];

lli ans[10];
lli memo[maxN][10]; int target;
lli solve(int i = 0, int d = 0)
{
  if (i == n) return d == target ? 0 : -2;
  lli &ans = memo[i][d];
  if (ans != -1) return ans;
  lli notPut = solve(i + 1, d), put = solve(i + 1, (d + a[i]) % 10);
  return ans = max(notPut, put == -2 ? -2 : put + a[i]);
}

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);

    for (int i = 0; i < 10; i++)
    {
      memset(memo, -1, sizeof(memo));
      target = i;
      ans[i] = solve();
      if (ans[i] == -2) ans[i] = -1;
      printf("%lld%c", ans[i], i < 10 - 1 ? ' ' : '\n');
    }
  }
  return 0;
}