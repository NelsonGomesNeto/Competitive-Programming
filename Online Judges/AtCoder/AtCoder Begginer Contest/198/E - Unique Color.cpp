#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
int c[maxN];
vector<int> tree[maxN];

set<int> ans;
map<int, int> colors;
void dfs(int u = 0, int prv = -1)
{
  if (!colors.count(c[u]))
  {
    ans.insert(u);
    colors[c[u]] = 0;
  }
  colors[c[u]]++;

  for (int v: tree[u])
    if (v != prv)
      dfs(v, u);

  if (--colors[c[u]] == 0)
    colors.erase(c[u]);
}

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &c[i]);
      tree[i].clear();
    }

    for (int i = 1; i < n; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      tree[u].push_back(v), tree[v].push_back(u);
    }

    colors.clear();
    ans.clear();
    dfs();
    for (int u: ans)
      printf("%d\n", u + 1);
  }
  return 0;
}