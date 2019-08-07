#include <bits/stdc++.h>
using namespace std;
int inf = 1<<20, dp[51][51][256];

int knap(char s[], int i, int k, char prev)
{
  if (!k) return(0);
  if (!s[i]) return(inf);

  if (dp[i][k][prev] == -1)
  {
    int ans = knap(s, i + 1, k, prev);
    if (s[i] - 1 > prev)
      ans = min(ans, s[i] - 'a' + 1 + knap(s, i + 1, k - 1, s[i]));
    dp[i][k][prev] = ans;
  }
  return(dp[i][k][prev]);
}

int solve(char s[], int k)
{
  int ans = 0; char prev = ' ';
  for (int i = 0; s[i] && k; i ++)
    if (s[i] - 1 > prev)
    {
      ans += s[i] - 'a' + 1;
      prev = s[i];
      k --;
    }
  return(!k ? ans : inf);
}

int main()
{
  int n, k; scanf("%d %d", &n, &k);
  char s[n + 1]; scanf("\n%s", s);
  sort(s, s + n);

  memset(dp, -1, sizeof(dp));
  int ans = solve(s, k);//knap(s, 0, k, ' ');
  printf("%d\n", ans >= inf ? -1 : ans);

  return(0);
}
