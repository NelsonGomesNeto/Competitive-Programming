#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
2*x - y = k
y = 2*x - k
*/

const int maxN = 2e5; int n; lli k;
lli x[maxN];
set<lli> has;

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %lld", &n, &k);
    has.clear();
    for (int i = 0; i < n; i++)
    {
      scanf("%lld", &x[i]);
      has.insert(x[i]);
    }
    lli minimum = 5*min(*min_element(x, x+n), k);
    lli maximum = 5*max(*max_element(x, x+n), k);
    bool can = false;

    priority_queue<pair<lli, lli>, vector<pair<lli, lli>>, greater<pair<lli, lli>>> pq;
    pq.push({0, k});
    set<lli> visited;
    while (!pq.empty())
    {
      lli u = pq.top().second; pq.pop();
      if (visited.count(u)) continue;
      visited.insert(u);

      if (has.count(u))
      {
        can = true;
        break;
      }

      for (int i = 0; i < n; i++)
      {
        lli v = 2*x[i] - u;
        if (v >= minimum && v <= maximum)
          pq.push({k - v, v});
      }
    }

    priority_queue<pair<lli, lli>, vector<pair<lli, lli>>, less<pair<lli, lli>>> pq2;
    pq2.push({0, k});
    visited.clear();
    while (!pq2.empty())
    {
      lli u = pq2.top().second; pq2.pop();
      if (visited.count(u)) continue;
      visited.insert(u);

      if (has.count(u))
      {
        can = true;
        break;
      }

      for (int i = 0; i < n; i++)
      {
        lli v = 2*x[i] - u;
        if (v >= minimum && v <= maximum)
          pq2.push({k - v, v});
      }
    }
    printf("%s\n", can ? "YES" : "NO");
  }
  return 0;
}
