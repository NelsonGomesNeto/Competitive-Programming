#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
lli A, B, a[maxN], b[maxN];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%lld %lld %d", &A, &B, &n);
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);
    for (int i = 0; i < n; i++)
      scanf("%lld", &b[i]);
    
    bool can = true;
    priority_queue<pair<lli, int>> pq;
    for (int i = 0; i < n; i++)
      pq.push({-a[i], i});
    while (!pq.empty())
    {
      if (B <= 0)
      {
        can = false;
        break;
      }
      lli canDo = pq.top().first; int idx = pq.top().second; pq.pop();
      lli newCanDo = B / a[idx] + (B % a[idx] != 0);
      // if (newCanDo < canDo)
      // {
      //   pq.push({newCanDo - (b[idx] / A + (b[idx] % A != 0)), idx});
      //   continue;
      // }
      canDo = newCanDo;

      lli hits = b[idx] / A + (b[idx] % A != 0);
      if (canDo < hits)
      {
        can = false;
        break;
      }
      B -= hits * a[idx];
    }

    printf("%s\n", can ? "YES" : "NO");
  }
  return 0;
}