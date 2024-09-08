#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e3; int n;
lli a[maxN];
vector<pair<lli, int>> all;

lli memo[maxN][maxN];
lli solve(int i = 0, int lo = 0, int hi = n - 1)
{
  if (i == n) return 0;
  if (memo[lo][hi] != -1) return memo[lo][hi];

  lli ans = max
  (
    solve(i + 1, lo + 1, hi) + a[all[i].second] * abs(all[i].second - lo),
    solve(i + 1, lo, hi - 1) + a[all[i].second] * abs(all[i].second - hi)
  );
  return memo[lo][hi] = ans;
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    all.clear();
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);

    
    for (int i = 0; i < n; i++)
    {
      int left = i, right = n - i - 1;
      all.push_back({a[i], i});
    }
    sort(all.begin(), all.end());
    reverse(all.begin(), all.end());

    memset(memo, -1, sizeof(memo));
    lli ans = solve();
    printf("%lld\n", ans);
  }
  return 0;
}
