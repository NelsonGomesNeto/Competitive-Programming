#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int n;

ldouble solve(int s = n)
{
  if (s == 0) return 0;
  ldouble ans = 0;
  for (int t = 1; t <= s; t ++)
    ans = max(ans, solve(s - t) + (ldouble) t / s);
  return ans;
}

int main()
{
  DEBUG
    for (n = 1; n <= 100; n ++)
    {
      printf("%d %.15Lf\n", n, solve());
    }

  while (scanf("%d", &n) != EOF)
  {
    ldouble ans = 0;
    for (ldouble i = 1; i <= n; i ++)
      ans += 1 / i;
    printf("%.15Lf\n", ans);
  }
  return 0;
}