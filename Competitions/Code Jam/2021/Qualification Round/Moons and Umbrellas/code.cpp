#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3; int n;
const int inf = 1e6;
char s[maxN + 1]; int x, y;

int getCost(char a, char b)
{
  if (a == 'C' && b == 'J')
    return x;
  else if (a == 'J' && b == 'C')
    return y;
  return 0;
}
int memo[maxN][2];
int solve(int i = 0, char prv = '\0')
{
  if (i == n)
    return 0;

  int &ans = memo[i][i == 0 ? 0 : prv == 'J' ? 0 : 1];
  if (ans != -inf)
    return ans;

  if (s[i] == '?')
    ans = min(solve(i + 1, 'J') + getCost(prv, 'J'), solve(i + 1, 'C') + getCost(prv, 'C'));
  else
    ans = solve(i + 1, s[i]) + getCost(prv, s[i]);
  return ans;
}

int main()
{
  int t;
  while (~scanf("%d", &t))
  {
    for (int tt = 1; tt <= t; tt++)
    {
      scanf("%d %d %s", &x, &y, s); n = strlen(s);
      for (int i = 0; i < n; i++)
        memo[i][0] = memo[i][1] = -inf;
      int ans = solve();
      printf("Case #%d: %d\n", tt, ans);
    }
  }
  return 0;
}