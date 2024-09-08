#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
lli w[maxN];
vector<int> tree[maxN];
bool done[maxN];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
      scanf("%lld", &w[i]);
    for (int i = 0; i < n; i++) tree[i].clear();
    for (int i = 1; i < n; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      tree[u].push_back(v), tree[v].push_back(u);
    }

    priority_queue<lli> pq;
    for (int i = 0; i < n; i++) done[i] = false;
    for (int i = 0; i < n; i++)
      for (int j = 1; j < tree[i].size(); j++)
        pq.push(w[i]);

    lli ans = 0;
    for (int i = 0; i < n; i++) ans += w[i];
    for (int i = 0; i < n - 1; i++)
    {
      printf("%lld%c", ans, i < n - 2 ? ' ' : '\n');
      if (!pq.empty())
      {
        ans += pq.top();
        pq.pop();
      }
    }
  }
  return 0;
}
