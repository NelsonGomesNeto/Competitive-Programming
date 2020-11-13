#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxV = 1e5, maxLog = 20; int n, logn, m, q;
vector<int> graph[maxV], tree[maxV];
bool visited[maxV], articulation[maxV]; int low[maxV], in[maxV], t = 0;
vector<pair<int, int>> bridges;
void dfs(int u, int prv)
{
  visited[u] = true;
  in[u] = low[u] = ++ t; int children = 0;
  for (auto v: graph[u])
  {
    if (v == prv) continue;
    if (visited[v]) low[u] = min(low[u], in[v]);
    else
    {
      tree[u].push_back(v);
      dfs(v, u);
      low[u] = min(low[u], low[v]);
      if (low[v] > in[u]) bridges.push_back({u, v});
      if (low[v] >= in[u] && prv != -1) articulation[u] = true;
      children++;
    }
  }
  if (prv == -1 && children > 1) articulation[u] = true;
}
void tarjan()
{
  memset(visited, false, sizeof(visited));
  memset(articulation, false, sizeof(articulation));
  bridges.clear();
  t = 0;
  for (int i = 0; i < n; i ++)
    if (!visited[i])
      dfs(i, -1);
}

int level[maxV], artSum[maxV], ancestor[maxV][maxLog], logDP[maxV + 1];
void dfs(int u)
{
  visited[u] = true;
  for (int v: tree[u])
  {
    level[v] = level[u] + 1, ancestor[v][0] = u;
    artSum[v] = artSum[u] + articulation[v];
    dfs(v);
  }
}
void buildLCA()
{
  memset(visited, false, sizeof(visited));
  for (int i = 0; i < n; i++)
    if (!visited[i])
    {
      level[i] = ancestor[i][0] = 0;
      artSum[i] = articulation[i];
      dfs(i);
    }

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
    if (diff & 1)
      u = ancestor[u][i];

  if (u == v) return(u);

  // (i = logn - 1; i >= 0; i --) works as well
  for (int i = logDP[level[u] - 1]; ancestor[u][0] != ancestor[v][0]; i --)
    if (ancestor[u][i] != ancestor[v][i])
      u = ancestor[u][i], v = ancestor[v][i];

  return ancestor[u][0];
}

int lolsum;
bool lol(int u, int target)
{
  if (visited[u]) return false;
  visited[u] = true;
  if (u == target) return true;
  for (int v: graph[u])
    if (lol(v, target))
    {
      lolsum += articulation[v];
      return true;
    }
  return false;
}
int getArtSum(int u, int v)
{
  // if (level[u] > level[v]) swap(u, v);
  // lolsum = 0;
  // memset(visited, false, sizeof(visited));
  // lol(u, v);
  // return lolsum - articulation[v];
  int lca = LCA(u, v);
  int ans = artSum[u] + artSum[v] - 2*artSum[lca];
  printf("\t%d %d %d | %d %d %d\n", u + 1, v + 1, lca + 1, articulation[u], articulation[v], articulation[lca]);
  if (articulation[u] && u != lca) ans--;
  if (articulation[v] && v != lca) ans--;
  if (u != lca && v != lca && articulation[lca]) ans--;
  return ans;
}

int main()
{
  logDP[1] = 0; for (int i = 2; i <= maxV; i ++) logDP[i] = logDP[i >> 1] + 1;
  while (scanf("%d %d", &n, &m) != EOF)
  {
    for (int i = 0; i < n; i++) tree[i].clear(), graph[i].clear();
    logn = ceil(log2(n));
    for (int i = 0; i < m; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      graph[u].push_back(v), graph[v].push_back(u);
    }

    tarjan();
    buildLCA();

    int q; scanf("%d", &q);
    while (q--)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;

      int ans = 2 + getArtSum(u, v);
      DEBUG printf("%d %d - %d\n", u + 1, v + 1, ans);
      else printf("%d\n", ans);
    }
  }
  return 0;
}