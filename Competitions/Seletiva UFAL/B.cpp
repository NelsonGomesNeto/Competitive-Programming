#include <bits/stdc++.h>
using namespace std;

const int maxN = 2e5; int n;
vector<int> tree[maxN]; int color[maxN];
vector<int> colorTree[maxN]; int nodeAmount;

void dfs(int u, int prv, int node)
{
  for (int v: tree[u])
  {
    if (v == prv) continue;
    if (color[u] != color[v])
    {
      nodeAmount ++;
      colorTree[node].push_back(nodeAmount), colorTree[nodeAmount].push_back(node);
      dfs(v, u, nodeAmount);
    }
    else dfs(v, u, node);
  }
}

int dist[maxN];
void height(int u, int prv)
{
  for (int v: colorTree[u])
  {
    if (v == prv) continue;
    dist[v] = dist[u] + 1;
    height(v, u);
  }
}

int getMostDistant()
{
  int mostDistant = 0;
  for (int i = 0; i < n; i ++)
    if (dist[i] > dist[mostDistant])
      mostDistant = i;
  return(mostDistant);
}

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i ++) scanf("%d", &color[i]);
  for (int i = 0, u, v; i < n - 1; i ++)
  {
    scanf("%d %d", &u, &v); u --, v --;
    tree[u].push_back(v), tree[v].push_back(u);
  }

  dfs(0, -1, 0);

  height(0, -1);
  int mostDistant = getMostDistant();
  memset(dist, 0, sizeof(dist));
  height(mostDistant, -1);
  mostDistant = getMostDistant();
  printf("%d\n", (dist[mostDistant] >> 1) + (dist[mostDistant] & 1));

  return(0);
}
