#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e5, maxK = 1e5; int n, k, p;
lli a[maxN];
vector<lli> even, odd;
vector<vector<lli>> groups;

int main()
{
  scanf("%d %d %d", &n, &k, &p);;
  for (int i = 0; i < n; i ++)
  {
    scanf("%lld", &a[i]);
    if (a[i] & 1) odd.push_back(a[i]);
    else even.push_back(a[i]);
  }

  int e = 0, o = 0;
  while (e < even.size() && groups.size() < p)
  {
    groups.push_back(vector<lli>());
    groups[groups.size() - 1].push_back(even[e ++]);
  }
  while (groups.size() < p && o + 1 < odd.size())
  {
    groups.push_back(vector<lli>());
    groups[groups.size() - 1].push_back(odd[o ++]);
    groups[groups.size() - 1].push_back(odd[o ++]);
  }
  if (groups.size() == p)
  {
    while (groups.size() < k && o < odd.size())
    {
      groups.push_back(vector<lli>());
      groups[groups.size() - 1].push_back(odd[o ++]);
    }
    while (o + 1 < odd.size())
    {
      groups[groups.size() - 1].push_back(odd[o ++]);
      groups[groups.size() - 1].push_back(odd[o ++]);
    }
    while (e < even.size() && groups.size()) groups[0].push_back(even[e ++]);
    if (e == even.size() && o == odd.size() && groups.size() == k)
    {
      printf("YES\n");
      for (auto &g: groups)
      {
        printf("%d ", (int) g.size());
        for (int i = 0; i < g.size(); i ++) printf("%lld%c", g[i], i < g.size() - 1 ? ' ' : '\n');
      }
    }
    else printf("NO\n");
  }
  else printf("NO\n");

  return(0);
}