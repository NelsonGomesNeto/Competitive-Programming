#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n, k;
const int inf = 1e9;
int h[maxN];

int memo[maxN];
int solve(int i = 0)
{
  if (i >= n - 1) return i == n - 1 ? 0 : inf;
  int &ans = memo[i];
  if (ans != -1) return ans;

  ans = inf;
  for (int j = 1; j <= k; j++)
    ans = min(ans, solve(i + j) + abs(h[i + j] - h[i]));
  return ans;
}

int main()
{
  while (scanf("%d %d", &n, &k) != EOF)
  {
    for (int i = 0; i < n; i++)
      scanf("%d", &h[i]);

    memset(memo, -1, sizeof(memo));
    int ans = solve();
    printf("%d\n", ans);
  }
  return 0;
}