#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e3; int n, m;
int a[maxN];
int resp[maxN + 1];

int memo[maxN + 1][maxN][2];
int solve(int remaining = 0, int i = 0, bool deleting = false)
{
  if (remaining <= 0) return remaining == 0 ? (i == n ? 0 : 1) : 1e9;
  // if (reamining sum + sum < target) return 0;
  if (i == n) return 1e9;
  int& ans = memo[remaining][i][deleting];
  if (ans != -1) return ans;

  ans = 1e9;
  if (deleting)
    ans = min(solve(remaining, i + 1, true), solve(remaining - a[i], i + 1, false));
  else
    ans = min(solve(remaining, i + 1, true) + 1, solve(remaining - a[i], i + 1, false));

  return ans;
}

int main()
{
  int hehe = 0;
  while (~scanf("%d %d", &n, &m))
  {
    if (hehe++) printf("--------------------------\n");

    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);

    memset(memo, -1, sizeof(memo));
    for (int i = 1; i <= m; ++i)
    {
      resp[i] = solve(i);
      if (resp[i] == 1e9) resp[i] = -1;
    }

    for (int i = 1; i <= m; ++i)
      printf("%d\n", resp[i]);
  }
  return 0;
}
