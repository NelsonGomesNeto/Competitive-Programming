#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
vector<lli> a[maxN];
int mx[maxN];
int order[maxN];

bool can(lli x)
{
  for (int i = 0; i < n; i++)
  {
    for (int m: a[order[i]])
      if (m >= x)
        return false;
    x += a[order[i]].size();
  }
  return true;
}

bool cmp(int i, int j)
{
  return mx[i] < mx[j];
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
      a[i].clear();
      int k; scanf("%d", &k);
      a[i].resize(k);
      order[i] = i;
      for (int j = 0; j < k; j++)
      {
        scanf("%lld", &a[i][j]);
        a[i][j] -= j;
      }
      mx[i] = *max_element(a[i].begin(), a[i].end());
    }
    sort(order, order+n, cmp);

    lli lo = 0, hi = 1e18;
    while (lo < hi)
    {
      lli mid = (lo + hi) >> 1;
      if (can(mid)) hi = mid;
      else lo = mid + 1;
    }
    printf("%lld\n", lo);
  }
  return 0;
}
