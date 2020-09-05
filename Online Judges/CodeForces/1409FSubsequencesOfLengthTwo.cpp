#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 200; int n, k;
char s[maxN + 1], t[3];

int memo[maxN][maxN][maxN];
int solve(int i = 0, int before = 0, int subs = 0)
{
  if (i == n) return 0;
  if (memo[i][before][subs] != -1) return memo[i][before][subs];

  int ans = 0;
  for (char a = 'a'; a <= 'z'; a++)
    if (subs + (a != s[i]) <= k)
      ans = max(ans, solve(i + 1, before + (a == t[0]), subs + (a != s[i])) + before*(a == t[1]));

  return memo[i][before][subs] = ans;
}

int main()
{
  while (scanf("%d %d", &n, &k) != EOF)
  {
    scanf(" %s %s", s, t);

    memset(memo, -1, sizeof(memo));
    int ans = solve();
    printf("%d\n", ans);
  }
  return 0;
}