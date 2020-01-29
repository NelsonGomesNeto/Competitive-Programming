#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
lli a[maxN];

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i ++)
      scanf("%lld", &a[i]);
    set<lli> pq;
    for (int i = 0; i < n; i ++)
      pq.insert(a[i]);
    int ans = 0;
    while (!pq.empty())
    {
      lli u = *pq.rbegin(); pq.erase(*pq.rbegin());
      if (u & 1LL) continue;
      ans ++;
      pq.insert(u >> 1LL);
    }
    printf("%d\n", ans);
  }
  return 0;
}
