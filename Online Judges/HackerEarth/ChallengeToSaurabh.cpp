#include <bits/stdc++.h>
using namespace std;

/* Tutorial:
  if (cycles == 1) print("YES")
  else print("NO")
  To count the cycles, you can either use dfs + colors, or use DSU
  DSU:
    whenever you are to merge to nodes with same root, you're creating a cycle,
    since if they have the same root: they already had a path, now they have at least two
*/

const int maxN = 1e2; int n, m;
int parent[maxN];
int root(int u)
{
  if (parent[u] < 0) return(u);
  return(parent[u] = root(parent[u]));
}
int setSize(int u)
{
  return(-1 * parent[root(u)]);
}
void merge(int u, int v)
{
  u = root(u), v = root(v);
  if (u == v) return;
  if (parent[v] < parent[u]) swap(u, v);
  parent[u] += parent[v];
  parent[v] = u;
}

vector<int> graph[maxN];
int color[maxN], cycles;
void dfs(int u, int prv = -1)
{
  if (color[u])
  {
    cycles += color[u] == 1;
    return;
  }
  color[u] = 1;
  for (int v: graph[u])
    if (v != prv)
      dfs(v, u);
  color[u] = 2;
}

int main()
{
  memset(parent, -1, sizeof(parent));
  scanf("%d %d", &n, &m);
  int lol = 0;
  for (int i = 0, u, v; i < m; i ++)
  {
    scanf("%d %d", &u, &v); u --, v --;
    if (root(u) == root(v)) lol ++;
    // this will detect a cycle
    // since they have the same root, there were a path from u to v; now, there are two paths from u to v
    merge(u, v);
    graph[u].push_back(v), graph[v].push_back(u);
  }
  for (int i = 0; i < n; i ++)
    if (!color[i])
      dfs(i);
  // printf("%d %d\n", cycles, lol);
  printf("%s\n", cycles == 1 ? "YES" : "NO");
  return(0);
}