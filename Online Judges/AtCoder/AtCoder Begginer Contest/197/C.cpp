#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 20; int n;
lli a[maxN];

lli solve(int i = 0, lli currOr = 0, lli currXor = 0)
{
  if (i == n) return currXor ^ currOr;

  currOr |= a[i];
  lli ans = min(
    solve(i + 1, 0, currXor ^ currOr),
    solve(i + 1, currOr, currXor)
  );

  return ans;
}

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);

    lli ans = solve();
    printf("%lld\n", ans);
  }
  return 0;
}