#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;

/* Thinking:
Insertions and removals will only happen on leafs
So I might be able to recalculate LCA's DP in every insertion and just ignore
on removals
*/

const int maxN = 1e5, maxLog = ceil(log2(1e5));
vector<int> tree[maxN]; int root; bool inTree[maxN];
int level[maxN], ancestor[maxN][maxLog], nodeMap[maxN], revMap[maxN], nm;
void dfs(int u, int prev)
{
  for (int v: tree[u])
    if (v != prev)
    {
      level[v] = level[u] + 1, ancestor[v][0] = u;
      dfs(v, u);
    }
}
void build()
{
  level[root] = ancestor[root][0] = 0; dfs(root, -1);
  for (int i = 1; i < maxLog; i ++)
    for (int u = 0; u < maxN; u ++)
      ancestor[u][i] = ancestor[ancestor[u][i - 1]][i - 1];
}

void add(int u)
{
  for (int i = 1; i < maxLog; i ++) ancestor[u][i] = ancestor[ancestor[u][i - 1]][i - 1];
}

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    int u, v, p; scanf("%d", &p);
    memset(nodeMap, -1, sizeof(nodeMap)); memset(inTree, false, sizeof(inTree));
    nm = 0; for (int i = 0; i < maxN; i ++) tree[i].clear();
    for (int i = 0; i < p; i ++)
    {
      scanf("%d %d", &u, &v); u --, v --;
      if (nodeMap[u] == -1) { revMap[nm] = u; nodeMap[u] = nm ++; }
      inTree[nodeMap[u]] = true;
      if (v == -1) { root = nodeMap[u]; continue; }
      else if (nodeMap[v] == -1) { revMap[nm] = v; nodeMap[v] = nm ++; }
      u = nodeMap[u], v = nodeMap[v];
      tree[u].push_back(v); tree[v].push_back(u); inTree[v] = true;
    }
    build();
    DEBUG for (int i = 0; i < nm; i ++)
      printf("%d %d %d\n", i, revMap[i] + 1, level[i]);

    int op, q, k; scanf("%d", &q);
    while (q --)
    {
      scanf("%d %d", &op, &u); u --; if (nodeMap[u] == -1) { revMap[nm] = u; nodeMap[u] = nm ++; }
      u = nodeMap[u];
      if (op == 0) // insertion
      {
        scanf("%d", &v); v --; if (nodeMap[v] == -1) { revMap[nm] = v; nodeMap[v] = nm ++; }
        v = nodeMap[v];
        level[v] = level[u] + 1, ancestor[v][0] = u; add(v); inTree[v] = true;
      }
      else if (op == 1) // removal
        inTree[u] = false;
      else
      {
        scanf("%d", &k);
        if (!inTree[u] || level[u] < k) printf("0\n");
        else
        {
          for (int diff = k, i = 0; diff; diff >>= 1, i ++)
            if (diff & 1) u = ancestor[u][i];
          printf("%d\n", revMap[u] + 1);
        }
      }
    }
  }
  return(0);
}
