#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3; int n, r;
vector<int> tree[maxN];

int mbt(int u = 0, int prv = -1)
{
  vector<int> res;
  for (int v: tree[u])
    if (v != prv)
      res.push_back(1 + mbt(v, u));
  sort(res.begin(), res.end(), greater<int>());

  int ans = 0;
  for (int i = 0; i < res.size(); i++)
    ans = max(ans, i + res[i]);

  return ans;
}

int main()
{
  int t;
  while (scanf("%d", &t) != EOF)
    for (int tt = 1; tt <= t; tt++)
    {
      scanf("%d %d", &n, &r);
      r--;
      for (int i = 0; i < n; i++) tree[i].clear();

      for (int i = 1; i < n; i++)
      {
        int u, v; scanf("%d %d", &u, &v); u--, v--;
        tree[u].push_back(v), tree[v].push_back(u);
      }

      int ans = mbt(r);
      printf("%d\n", ans);
    }
  return 0;
}