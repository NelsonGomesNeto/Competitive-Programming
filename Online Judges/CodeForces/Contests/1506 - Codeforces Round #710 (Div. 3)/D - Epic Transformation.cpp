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
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);

    map<lli, int> cnt;
    for (int i = 0; i < n; i++)
    {
      if (!cnt.count(a[i]))
        cnt[a[i]] = 0;
      cnt[a[i]]++;
    }

    priority_queue<int> pq;
    for (auto &c: cnt)
      pq.push(c.second);
    while (pq.size() >= 2)
    {
      int a = pq.top(); pq.pop();
      int b = pq.top(); pq.pop();
      if (a - 1 >= 1)
        pq.push(a - 1);
      if (b - 1 >= 1)
        pq.push(b - 1);
    }

    int ans = 0;
    while (!pq.empty())
    {
      ans += pq.top();
      pq.pop();
    }
    printf("%d\n", ans);
  }
  return 0;
}
