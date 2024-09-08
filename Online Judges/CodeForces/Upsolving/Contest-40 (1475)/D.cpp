#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n, m;
const int inf = 1e7;
lli a[maxN]; int b[maxN];
vector<lli> apps[2], acc[2];

int lowerBound(lli target)
{
  int lo = 0, hi = apps[1].size();
  while (lo < hi)
  {
    int mid = (lo + hi) >> 1;
    if (acc[1][mid] >= target) hi = mid;
    else lo = mid + 1;
  }
  return acc[1][lo] >= target ? 2 * lo : inf;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    apps[0].clear(), apps[1].clear();
    scanf("%d %d", &n, &m);
    lli sum = 0;
    for (int i = 0; i < n; i++)
    {
      scanf("%lld", &a[i]);
      sum += a[i];
    }
    for (int i = 0; i < n; i++)
      scanf("%d", &b[i]);

    if (sum < m)
    {
      printf("-1\n");
      continue;
    }

    for (int i = 0; i < n; i++)
      apps[b[i] - 1].push_back(a[i]);
    for (int i = 0; i < 2; i++)
    {
      sort(apps[i].begin(), apps[i].end(), greater<lli>());
      acc[i].resize(apps[i].size() + 1);
      for (int j = 0; j < apps[i].size(); j++)
        acc[i][j + 1] = acc[i][j] + apps[i][j];
    }

    int ans = lowerBound(m);
    for (int i = 0; i < apps[0].size(); i++)
      ans = min(ans, (i + 1) + lowerBound(m - acc[0][i + 1]));

    printf("%d\n", ans);
  }
  return 0;
}
