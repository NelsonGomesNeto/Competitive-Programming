#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
  int n, k; scanf("%d %d", &n, &k);
  lli a[n]; map<lli, vector<int>> aMap;
  for (int i = 0; i < n; i ++)
  {
    scanf("%lld", &a[i]);
    aMap[a[i]].push_back(i);
  }

  lli total = 0, memo[n]; memset(memo, 0, sizeof(memo));
  for (int i = n - 2; i >= 1; i --)
  {
    int pos = lower_bound(aMap[a[i] * k].begin(), aMap[a[i] * k].end(), i + 1) - aMap[a[i] * k].begin();
    memo[i] = (aMap[a[i] * k].end() - aMap[a[i] * k].begin() - 1) - pos + 1;
    vector<int>::iterator it = lower_bound(aMap[a[i]].begin(), aMap[a[i]].end(), i + 1);
    if (it != aMap[a[i]].end()) memo[i] += memo[*it];
  }
  for (int i = 0; i < n - 2; i ++)
    if (aMap.count(a[i] * k))
    {
      vector<int>::iterator beginIt = aMap[a[i] * k].begin(), endIt = aMap[a[i] * k].end();
      vector<int>::iterator it = lower_bound(beginIt, endIt, i + 1);
      int pos = it == endIt ? 0 : *it;
      total += memo[pos];
    }
  printf("%lld\n", total);

  return(0);
}