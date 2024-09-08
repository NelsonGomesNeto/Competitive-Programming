#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n, a, b;
const int inf = 1e8 + 1;
char s[maxN + 1];

int memo[maxN][2][2];
int solve(int i = 0, bool detonated = false, bool hasPrv = false)
{
  // printf("%d %d %d\n", i, detonated, hasPrv);
  if (i == n) return hasPrv ? inf : 0;
  int &ans = memo[i][detonated][hasPrv];
  if (ans != -1) return ans;

  ans = inf;
  if (hasPrv)
  {
    if (s[i] == '0')
    {
      ans = min(ans, solve(i + 1, true, false) + b + a);
      ans = min(ans, solve(i + 1, false, true) + b);
    }
    else
    {
      ans = min(ans, solve(i + 1, true, false) + a);
      ans = min(ans, solve(i + 1, false, true));
    }
  }
  else if (detonated)
  {
    if (s[i] == '0')
    {
      ans = min(ans, solve(i + 1, true, false) + b);
      ans = min(ans, solve(i + 1, false, false));
    }
    else
      ans = min(ans, solve(i + 1, true, false));
  }
  else
  {
    if (s[i] == '1')
    {
      ans = min(ans, solve(i + 1, true, false) + a);
      ans = min(ans, solve(i + 1, false, true));
    }
    else
    {
      ans = min(ans, solve(i + 1, false, true) + b);
      ans = min(ans, solve(i + 1, true, false) + b + a);
      ans = min(ans, solve(i + 1, false, false));
    }
  }

  return ans;
}

int main()
{
  int t;
  while (scanf("%d", &t) != EOF)
    for (int tt = 0; tt < t; tt++)
    {
      scanf("%d %d", &a, &b);
      scanf(" %s", s);
      n = strlen(s);
      DEBUG printf("%d %d - %s %d\n", a, b, s, n);

      memset(memo, -1, sizeof(memo));
      int ans = solve();
      printf("%d\n", ans);
    }
  return 0;
}