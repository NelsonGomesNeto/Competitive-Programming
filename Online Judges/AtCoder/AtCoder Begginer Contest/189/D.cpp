#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 60; int n;
char s[maxN + 1][4];
bool isand[maxN];

lli memo[2][maxN];
lli solve(bool curr, int i = 0)
{
  if (i == n) return curr;
  lli &ans = memo[curr][i];
  if (ans != -1) return ans;

  ans = 0;
  for (int now = 0; now <= 1; now++)
    if (isand[i])
      ans += solve(curr & now, i + 1);
    else
      ans += solve(curr | now, i + 1);
  return ans;
}

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++)
    {
      scanf(" %s", s[i]);
      isand[i] = !strcmp(s[i], "AND");
    }

    memset(memo, -1, sizeof(memo));
    lli ans = solve(false) + solve(true);
    printf("%lld\n", ans);
  }
  return 0;
}