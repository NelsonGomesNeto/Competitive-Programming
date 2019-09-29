#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
vector<int> tree[maxN];
lli v[maxN];
struct Ans
{
  lli minus, plus;
  void merge(Ans other)
  {
    minus = max(minus, other.minus);
    plus = max(plus, other.plus);
  }
};
Ans dfs(int u = 0, int prv = -1)
{
  Ans ans = {0, 0};
  for (int v: tree[u])
    if (v != prv)
      ans.merge(dfs(v, u));
  v[u] = v[u] + ans.plus - ans.minus;
  if (v[u] > 0) ans.minus += v[u];
  if (v[u] < 0) ans.plus += -v[u];
  return ans;
}

int main()
{
  scanf("%d", &n);
  for (int i = 1; i < n; i ++)
  {
    int u, v; scanf("%d %d", &u, &v); u --, v --;
    tree[u].push_back(v), tree[v].push_back(u);
  }
  for (int i = 0; i < n; i ++) scanf("%lld", &v[i]);

  Ans ans = dfs();
  printf("%lld\n", ans.minus + ans.plus);

  return 0;
}