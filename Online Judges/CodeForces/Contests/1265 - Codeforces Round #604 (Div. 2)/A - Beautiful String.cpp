#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5 + 1; int n;
char s[maxN];

int memo[4][maxN], chosen[4][maxN];
int solve(int i = 0, int prv = 0)
{
  if (i == n) return true;
  if (memo[prv][i] != -1) return memo[prv][i];
  int ans = 0;
  if (s[i] != '?' && prv + 'a' - 1 != s[i])
  {
    ans = solve(i + 1, s[i] - 'a' + 1);
    chosen[prv][i] = s[i];
  }
  else if (prv + 'a' - 1 != s[i])
  {
    for (int j = 'a'; j <= 'c' && !ans; j ++)
      if (prv - 1 + 'a' != j && solve(i + 1, j - 'a' + 1))
      {
        ans = true;
        chosen[prv][i] = j;
      }
  }
  return memo[prv][i] = ans;
}

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    scanf(" %s", s);
    n = strlen(s);
    for (int i = 0; i < n; i ++)
      memo[0][i] = memo[1][i] = memo[2][i] = memo[3][i] = -1;
    bool can = solve();
    if (!can)
    {
      printf("-1\n");
      continue;
    }
    for (int i = 0, prv = 0; i < n; i ++)
    {
      s[i] = chosen[prv][i];
      prv = s[i] - 'a' + 1;
    }
    printf("%s\n", s);
  }
  return 0;
}
