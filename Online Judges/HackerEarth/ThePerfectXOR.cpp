#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
using namespace std;
 
const int maxN = 3e5; int n, m;
vector<int> graph[maxN], tree[maxN];
vector<pair<int, int>> bridges;
lli weight[maxN], below[maxN];
 
bool visited[maxN];
int in[maxN], low[maxN], t; bool articulation[maxN];
lli weightsSum;
void tarjan(int u = 0, int prv = -1)
{
  visited[u] = true;
  in[u] = low[u] = ++ t;
  for (int v: graph[u])
    if (!visited[v])
    {
      tarjan(v, u);
      tree[u].push_back(v);
      low[u] = min(low[u], low[v]);
      if (low[v] > in[u])
      {
        bridges.push_back({u, v});
        articulation[u] = graph[u].size() > 1, articulation[v] = graph[v].size() > 1;
      }
    }
    else if (v != prv) low[u] = min(low[u], in[v]);
}
 
lli dfs(int u = 0)
{
  below[u] = weight[u];
  for (int v: tree[u]) below[u] += dfs(v);
  return(below[u]);
}
 
lli removeNode(int u)
{
  lli ans = 0, sum = 0;
  for (int v: tree[u])
  {
    if (low[v] < in[u]) continue; // v is part of the above group
    ans ^= below[v], sum += below[v];
  }
  ans ^= weightsSum - sum - weight[u];
  return(ans);
}
 
int main()
{
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; i ++)
  {
    scanf("%lld", &weight[i]);
    weightsSum += weight[i];
  }
  for (int i = 0, u, v; i < m; i ++)
  {
    scanf("%d %d", &u, &v); u --, v --;
    graph[u].push_back(v), graph[v].push_back(u);
  }
  tarjan();
  dfs();
 
  lli ans = -1;
  for (int i = 0; i < n; i ++)
    if (articulation[i])
      ans = max(ans, removeNode(i));
  printf("%lld\n", ans);
 
  return(0);
}
