#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e5; int n, m;
int k[maxN]; lli c[maxN];
bool done[maxN];

int main()
{
  int t;
  while (~scanf("%d", &t))
    for (int tt = 1; tt <= t; tt++)
    {
      scanf("%d %d", &n, &m);
      for (int i = 0; i < n; i++)
      {
        scanf("%d", &k[i]);
        k[i]--;
      }
      for (int i = 0; i < m; i++)
        scanf("%lld", &c[i]), done[i] = false;

      sort(k, k+n, greater<int>());
      priority_queue<lli, vector<lli>, greater<lli>> pq;
      int at = 0;
      lli ans = 0;
      for (int i = 0; i < n; i++)
      {
        for (; at <= k[i]; at++)
          pq.push(c[at]);

        if (pq.empty() || c[k[i]] <= pq.top())
        {
          ans += c[k[i]];
          DEBUG printf("\tmoney %lld\n", c[k[i]]);
        }
        else
        {
          ans += pq.top();
          DEBUG printf("\tgift  %lld\n", pq.top());
          pq.pop();
        }
      }
      printf("%lld\n", ans);
    }
  return 0;
}
