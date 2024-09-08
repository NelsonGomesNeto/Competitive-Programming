#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 8e5; int n;
vector<vector<int>> tree;
int visited[maxN];

const int maxLog = 20; int logn;
int level[maxN], ancestor[maxN][maxLog], logDP[maxN + 1];
void dfs(int u, int prv = -1)
{
  for (int v: tree[u])
    if (v != prv)
    {
      level[v] = level[u] + 1, ancestor[v][0] = u;
      dfs(v, u);
    }
}
void build()
{
  level[0] = ancestor[0][0] = 0; dfs(0);
  for (int i = 1; i < logn; i ++)
    for (int u = 0; u < n; u ++)
    {
      ancestor[u][i] = ancestor[ancestor[u][i - 1]][i - 1];
      // If you want to add something about the path, like weight:
      // weight[u][i] = combination of weight[u][i - 1] and weight[ancestor[u][i - 1]][i - 1]
    }
}
int LCA(int u, int v)
{
  if (level[v] > level[u]) swap(u, v);

  for (int diff = level[u] - level[v], i = 0; diff; diff >>= 1, i ++)
    if (diff & 1) u = ancestor[u][i];

  if (u == v) return(u);

  // (i = logn - 1; i >= 0; i --) works as well
  for (int i = logDP[level[u] - 1]; ancestor[u][0] != ancestor[v][0]; i --)
    if (ancestor[u][i] != ancestor[v][i])
      u = ancestor[u][i], v = ancestor[v][i];

  return(ancestor[u][0]);
}

int f[maxN];
vector<int> freq[maxN];
set<pair<int, int>> used;

int main()
{
  logDP[1] = 0; for (int i = 2; i <= maxN; i ++) logDP[i] = logDP[i >> 1] + 1;

  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    logn = ceil(log2(n));

    tree.clear();
    tree.resize(n);
    for (int i = 0; i < n; i++) freq[i].clear(), visited[i] = 0;

    for (int i = 1; i < n; i++)
    {
      int a, b; scanf("%d %d", &a, &b); a--, b--;
      tree[a].push_back(b), tree[b].push_back(a);
    }
    build();

    for (int i = 0; i < n; i++)
    {
      scanf("%d", &f[i]); f[i]--;
      freq[f[i]].push_back(i);
    }

    DEBUG
      for (int u = 0; u < n; u++)
        for (int v: tree[u])
          printf("%d,%d %d,%d\n", u, f[u], v, f[v]);

    used.clear();

    vector<pair<int, pair<int, int>>> hehe;
    for (int i = 0; i < n; i++)
    {
      if (freq[i].size() >= 2)
      {
        int lca = LCA(freq[i][0], freq[i][1]);
        for (int j = 2; j < freq[i].size(); j++)
          lca = LCA(lca, freq[i][j]);

        DEBUG {
          printf("freq %d, lca %d\n\t", i, lca);
          for (int j = 0; j < freq[i].size(); j++)
            printf("%d%c", freq[i][j], j + 1 < freq[i].size() ? ' ' : '\n');
        }

        hehe.push_back(make_pair(level[lca], make_pair(lca, i)));
      }
    }
    sort(hehe.begin(), hehe.end());
    // reverse(hehe.begin(), hehe.end());

    for (auto &he: hehe)
    {
      int lca = he.second.first, i = he.second.second;
      for (int u: freq[i])
      {
        while (u != lca && !visited[u])
        {
          used.insert(make_pair(u, ancestor[u][0]));
          visited[u] = 1;
          u = ancestor[u][0];
        }
        visited[u] = 1;
      }
    }

    int ans = n - 1 - (int)used.size();
    printf("Case #%d: %d\n", tt, ans);
  }
  return 0;
}