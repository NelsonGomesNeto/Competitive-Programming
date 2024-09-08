#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 101; int n;
char s[maxN];

int memo[maxN][maxN];
int solve(int i = 0, int open = 0)
{
  if (open < 0) return false;
  if (i == n) return open == 0;
  int &ans = memo[i][open];
  if (ans != -1) return ans;

  ans = 0;
  if (s[i] == '(') ans = solve(i + 1, open + 1);
  if (s[i] == ')') ans = solve(i + 1, open - 1);
  if (s[i] == '?') ans = max(solve(i + 1, open + 1), solve(i + 1, open - 1));
  return ans;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf(" %s", s);
    n = strlen(s);

    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        memo[i][j] = -1;
    int ans = solve();
    printf("%s\n", ans ? "YES" : "NO");
  }
  return 0;
}