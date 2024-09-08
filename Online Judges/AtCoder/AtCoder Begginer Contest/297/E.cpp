#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 10;
int n, k;
lli a[maxN];

set<lli> done;
lli dijkstra()
{
  priority_queue<lli, vector<lli>, greater<lli>> pq;
  pq.push(0), done.clear();
  while (!pq.empty())
  {
    lli x = pq.top();
    pq.pop();
    if (done.count(x)) continue;
    done.insert(x);
    // printf("\t%lld %d\n", x, (int)done.size());
    if (done.size() == k + 1) break;

    for (int i = 0; i < n; ++i)
    {
      lli y = x + a[i];
      if (done.count(y)) continue;
      pq.push(y);
    }
  }
  return *prev(done.end());
}

int main()
{
  while (~scanf("%d %d", &n, &k))
  {
    for (int i = 0; i < n; ++i)
      scanf("%lld", &a[i]);

    lli ans = dijkstra();
    printf("%lld\n", ans);
  }
  return 0;
}
