#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n, k;
int a[maxN];
map<int, int> cnt;
map<int, int> minCnt, maxCnt;
map<int, int> minAcc, maxAcc;

int main()
{
  int t; scanf("%d", &t);
  while (t--)
  {
    cnt.clear(), minCnt.clear(), maxCnt.clear();
    minAcc.clear(), maxAcc.clear();
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++)
      scanf("%d", &a[i]);

    for (int i = 0, j = n - 1; i < j; i++, j--)
    {
      if (!cnt.count(a[i] + a[j]))
        cnt[a[i] + a[j]] = 0;
      cnt[a[i] + a[j]]++;

      int minimum = min(a[i], a[j]) + 1;
      if (!minCnt.count(minimum))
        minCnt[minimum] = 0;
      minCnt[minimum]++;

      int maximum = max(a[i], a[j]) + k;
      if (!maxCnt.count(maximum))
        maxCnt[maximum] = 0;
      maxCnt[maximum]++;

      DEBUG printf("%d - %d %d %d\n", i, a[i] + a[j], minimum, maximum);
    }

    minCnt[3*k] = maxCnt[3*k] = 0;
    for (auto i = minCnt.begin(); i->first != 3*k; i++)
      minAcc[next(i)->first] = minAcc[i->first] + i->second;
    for (auto i = maxCnt.begin(); i->first != 3*k; i++)
      maxAcc[next(i)->first] = maxAcc[i->first] + i->second;

    int ans = n;
    for (int i = 2; i <= 2*k; i++)
    {
      int oneMovement = (n >> 1) - (cnt.count(i) ? cnt[i] : 0);
      int minMovement = minAcc.rbegin()->second - minAcc.lower_bound(i + 1)->second;
      int maxMovement = maxAcc.upper_bound(i - 1)->second - maxAcc.begin()->second;
      DEBUG printf("\t%d | %d %d %d\n", i, oneMovement, minMovement, maxMovement);
      ans = min(ans, oneMovement + minMovement + maxMovement);
    }
    printf("%d\n", ans);
  }
  return 0;
}
