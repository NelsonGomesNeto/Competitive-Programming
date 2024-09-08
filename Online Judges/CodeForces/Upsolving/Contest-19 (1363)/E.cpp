#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
lli a[maxN]; int b[maxN], c[maxN];
vector<int> tree[maxN];

int cnt[2];
lli solve(int u = 0, int prv = -1, lli minA = a[0])
{
  int before[2] = {cnt[0], cnt[1]};
  if (b[u] != c[u]) cnt[b[u]]++;
  lli ans = 0;
  for (int v: tree[u])
    if (v != prv)
      ans += solve(v, u, min(minA, a[v]));

  int delta = min(cnt[0] - before[0], cnt[1] - before[1]);
  ans += minA * delta * 2;
  cnt[0] -= delta, cnt[1] -= delta;
  return ans;
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    bool can = true;
    int bb = 0, cc = 0;
    for (int i = 0; i < n; i++)
    {
      scanf("%lld %d %d", &a[i], &b[i], &c[i]), tree[i].clear();
      bb += b[i], cc += c[i];
    }
    if (bb != cc) can = false;

    for (int i = 1; i < n; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      tree[u].push_back(v), tree[v].push_back(u);
    }

    cnt[0] = cnt[1];
    lli ans = can ? solve() : -1;
    printf("%lld\n", ans);
  }
  return 0;
}
