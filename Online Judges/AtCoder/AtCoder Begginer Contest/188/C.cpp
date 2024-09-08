#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 16; int n;
lli a[1 << maxN];

int main()
{
  while (~scanf("%d", &n))
  {
    list<lli> pq, npq;
    for (int i = 0; i < (1 << n); i++)
    {
      scanf("%lld", &a[i]);
      pq.push_back(a[i]);
    }

    while (pq.size() > 2)
    {
      npq = list<lli>();
      while (!pq.empty())
      {
        lli a = *pq.begin(); pq.pop_front();
        lli b = *pq.begin(); pq.pop_front();
        npq.push_back(a > b ? a : b);
      }
      pq = npq;
    }

    lli ans = *pq.begin(); pq.pop_front();
    ans = min(ans, *pq.begin());
    for (int i = 0; i < (1 << n); i++)
      if (a[i] == ans)
      {
        ans = i + 1;
        break;
      }
    printf("%lld\n", ans);
  }
  return 0;
}