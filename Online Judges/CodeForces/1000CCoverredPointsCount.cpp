#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;
#define lli long long int

int main()
{
  int n; scanf("%d", &n);
  pair<lli, lli> a[n];
  vector<lli> in, out; set<lli> aa; vector<lli> all;
  for (int i = 0; i < n; i ++)
  {
    scanf("%lld %lld", &a[i].first, &a[i].second);
    in.push_back(a[i].first); out.push_back(a[i].second);
    aa.insert(a[i].first); aa.insert(a[i].second);
  }
  sort(in.begin(), in.end());
  sort(out.begin(), out.end());
  for (auto i: aa) all.push_back(i);

  int open = 0; lli total[n + 1]; memset(total, 0, sizeof(total));
  for (int i = 0; i < all.size(); i ++)
  {
    lli point = all[i];
    open += upper_bound(in.begin(), in.end(), point) - lower_bound(in.begin(), in.end(), point);
    total[open] ++;
    open -= upper_bound(out.begin(), out.end(), point) - lower_bound(out.begin(), out.end(), point);
    if (i + 1 < all.size()) total[open] += all[i + 1] - all[i] - 1;
    DEBUG printf("%lld %d\n", point, open);
    DEBUG for (int i = 1; i <= n; i ++) printf("%lld%c", total[i], i < n ? ' ' : '\n');
  }

  for (int i = 1; i <= n; i ++) printf("%lld%c", total[i], i < n ? ' ' : '\n');

  return(0);
}