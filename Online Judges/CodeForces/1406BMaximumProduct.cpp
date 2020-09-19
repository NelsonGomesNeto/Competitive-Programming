#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
lli a[maxN];
vector<lli> v[3];

lli solve(int done = 0, lli val = 1, int i = 0, int ii = v[0].size() - 1, int j = 0, int jj = v[1].size() - 1)
{
  if (done == 5) return val;

  lli ans = -1e18;
  if (i <= ii)
  {
    if (i < v[0].size())
      ans = max(ans, solve(done + 1, val * v[0][i], i + 1, ii, j, jj));
    if (ii >= 0)
      ans = max(ans, solve(done + 1, val * v[0][ii], i, ii - 1, j, jj));
  }
  if (j <= jj)
  {
    if (j < v[1].size())
      ans = max(ans, solve(done + 1, val * v[1][j], i, ii, j + 1, jj));
    if (jj >= 0)
      ans = max(ans, solve(done + 1, val * v[1][jj], i, ii, j, jj - 1));
  }
  return ans;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    for (int j = 0; j < 3; j++) v[j].clear();
    for (int i = 0; i < n; i++)
    {
      scanf("%lld", &a[i]);
      if (a[i] > 0) v[0].push_back(a[i]);
      else if (a[i] < 0) v[1].push_back(a[i]);
      else v[2].push_back(a[i]);
    }
    sort(v[0].begin(), v[0].end(), greater<lli>());
    sort(v[1].begin(), v[1].end(), greater<lli>());

    lli ans = v[2].empty() ? -1e18 : 0;
    ans = max(ans, solve());

    printf("%lld\n", ans);
  }
  return 0;
}
