#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e3; int n, k;
int a[maxN];

int memo[maxN][maxN + 1];
int solve(int i = 0, int idx = 1, int good = 0)
{
  if (good == k) return 0;
  if (i == n) return 1e6;
  int &ans = memo[i][idx];
  if (ans != -1) return ans;

  ans = 1e6;
  if (a[i] == idx) ans = min(ans, solve(i + 1, idx + 1, good + 1));
  ans = min(ans, solve(i + 1, idx, good) + 1);
  ans = min(ans, solve(i + 1, idx + 1, good));

  return ans;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++)
      scanf("%d", &a[i]);

    memset(memo, -1, sizeof(memo));
    int ans = solve();
    if (ans >= 1e6) ans = -1;
    printf("%d\n", ans);
  }
  return 0;
}
