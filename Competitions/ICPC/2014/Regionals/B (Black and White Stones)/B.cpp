#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 5e3; lli a, b; int n;
char s[maxN + 1];
int blackAmount;

lli memo[maxN][maxN];
lli solve(int blacks = 0, int i = 0)
{
  if (blacks == blackAmount) return(0);
  if (i == n) return(1e16);
  if (s[i] == 'B' && i == blacks) return(solve(blacks + 1, i + 1));
  if (memo[blacks][i] == -1)
  {
    lli ans = solve(blacks, i + 1);
    ans = min(ans, a + solve(blacks + 1, i + 1));
    if (s[i] == 'B')
      ans = min(ans, (i - blacks) * (a - b) + solve(blacks + 1, i + 1));
    memo[blacks][i] = ans;
  }
  return(memo[blacks][i]);
}

int main()
{
  while (scanf("%lld %lld", &a, &b) != EOF)
  {
    blackAmount = 0;
    scanf(" %s", s); n = strlen(s);
    for (int i = 0; s[i]; i ++)
      blackAmount += s[i] == 'B';
    // memset(memo, -1, sizeof(memo));
    // lli ans = solve();

    lli ans = 0;
    for (int i = 0, j = n - 1; s[i] && i < j; i ++)
      if (s[i] == 'W') // swap with the last black
      {
        while (j > i && s[j] == 'W') j --;
        if (i == j) break;
        ans += min((j - i) * (a - b), a);
        j --;
      }
    printf("%lld\n", ans);
  }
  return(0);
}