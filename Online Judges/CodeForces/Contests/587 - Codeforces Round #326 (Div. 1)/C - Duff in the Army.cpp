#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e5, maxLog = ceil(log2(1e5)); int n, m, q, logn;
vector<int> tree[maxN], people[maxN], peopleInPath[maxN][maxLog];
int level[maxN], ancestor[maxN][maxLog];
void merge(vector<int> &res, vector<int> &a, vector<int> &b)
{
  res.clear(); int i = 0, j = 0;
  while ((i < a.size() || j < b.size()) && res.size() < 10)
  {
    if (i >= a.size()) res.push_back(b[j ++]);
    else if (j >= b.size()) res.push_back(a[i ++]);
    else if (a[i] < b[j]) res.push_back(a[i ++]);
    else if (b[j] < a[i]) res.push_back(b[j ++]);
    else i ++;
  }
}
void dfs(int u, int prev)
{
  for (int v: tree[u])
    if (v != prev)
    {
      level[v] = level[u] + 1, ancestor[v][0] = u;
      merge(peopleInPath[v][0], people[u], people[v]);
      dfs(v, u);
    }
}
void build()
{
  dfs(0, -1);
  for (int i = 1; i < logn; i ++)
    for (int u = 0; u < n; u ++)
    {
      ancestor[u][i] = ancestor[ancestor[u][i - 1]][i - 1];
      merge(peopleInPath[u][i], peopleInPath[u][i - 1], peopleInPath[ancestor[u][i - 1]][i - 1]);
    }
}
pair<int, vector<int>> LCA(int u, int v)
{
  vector<int> ans, aux;
  if (level[v] > level[u]) swap(u, v);
  for (int diff = level[u] - level[v], i = 0; diff; diff >>= 1, i ++)
    if (diff & 1)
    {
      merge(aux, ans, peopleInPath[u][i]); ans = aux;
      u = ancestor[u][i];
    }
  if (u == v) return(make_pair(u, ans));
  for (int i = logn - 1; i >= 0; i --)
    if (ancestor[u][i] != ancestor[v][i])
    {
      merge(aux, ans, peopleInPath[v][i]); merge(ans, aux, peopleInPath[u][i]);
      // printf("Here:"); for (int j = 0; j < ans.size(); j ++) printf(" %d", ans[j]); printf("\n");
      u = ancestor[u][i], v = ancestor[v][i];
    }
  merge(aux, ans, peopleInPath[v][0]); merge(ans, aux, peopleInPath[u][0]);
  return(make_pair(ancestor[u][0], ans));
}

int main()
{
  scanf("%d %d %d", &n, &m, &q); logn = ceil(log2(n));
  int u, v, a;
  for (int i = 0; i < n - 1; i ++)
  {
    scanf("%d %d", &u, &v); u --, v --;
    tree[u].push_back(v); tree[v].push_back(u);
  }
  for (int i = 0; i < m; i ++)
  {
    scanf("%d", &u); u --;
    if (people[u].size() < 10) people[u].push_back(i + 1);
  }
  build();

  while (q --)
  {
    scanf("%d %d %d", &u, &v, &a); u --, v --;
    if (u == v)
    {
      int toPrint = min(a, (int) people[u].size()); printf("%d", toPrint);
      for (int i = 0; i < toPrint; i ++) printf(" %d", people[u][i]);
      printf("\n");
    }
    else
    {
      pair<int, vector<int>> lca = LCA(u, v);
      int toPrint = min(a, (int) lca.second.size()); printf("%d", toPrint);
      for (int i = 0; i < toPrint; i ++) printf(" %d", lca.second[i]);
      printf("\n");
    }
  }
  return(0);
}
