#include <bits/stdc++.h>
using namespace std;
#define lli long long int

int main()
{
  int n; scanf("%d", &n);
  pair<lli, lli> a[n]; for (int i = 0; i < n; i ++) scanf("%lld %lld", &a[i].first, &a[i].second);
  sort(a, a+n);

  vector<lli> ans;
  lli lo = a[0].first, hi = a[0].second;
  for (int i = 0; i < n; i ++)
    if (a[i].first > hi)
    {
      ans.push_back(hi);
      lo = a[i].first, hi = a[i].second;
    }
    else
      lo = max(lo, a[i].first), hi = min(hi, a[i].second);
  ans.push_back(hi);

  printf("%d\n", (int) ans.size());
  for (int i = 0; i < ans.size(); i ++)
    printf("%lld%c", ans[i], i < ans.size() - 1 ? ' ' : '\n');
  return(0);
}