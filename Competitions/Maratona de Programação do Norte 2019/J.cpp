#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e5; int n;
int grades[maxN];

int parent[maxN], groupId[maxN];
int root(int u)
{
  if (parent[u] < 0) return(u);
  return(parent[u] = root(parent[u]));
}
void merge(int u, int v)
{
  u = root(u), v = root(v);
  if (u == v) return;
  if (parent[v] < parent[u]) swap(u, v);
  parent[u] += parent[v];
  parent[v] = u;
}
int setSize(int u)
{
  return(-1 * parent[root(u)]);
}

vector<vector<int>> groupsGrades;

int main()
{
  memset(parent, -1, sizeof(parent));
  scanf("%d", &n);
  for (int i = 0; i < n; i ++) scanf("%d", &grades[i]);

  int m; scanf("%d", &m);
  for (int i = 0, u, v; i < m; i ++)
  {
    scanf("%d %d", &u, &v); u --, v --;
    merge(u, v);
  }

  for (int i = 0; i < n; i ++)
    if (parent[i] < 0)
    {
      groupId[i] = groupsGrades.size();
      groupsGrades.push_back(vector<int>(101, 0));
    }
  for (int i = 0; i < n; i ++)
    groupsGrades[groupId[root(i)]][grades[i]] ++;

  int q; scanf("%d", &q);
  while (q --)
  {
    int op; scanf("%d", &op);
    if (op == 1)
    {
      int w; scanf("%d", &w); w --;
      int ans = 0;
      for (int i = 1, id = groupId[root(w)]; i < grades[w]; i ++)
        ans += groupsGrades[id][i];
      printf("%d\n", ans);
    }
    else
    {
      int w, k; scanf("%d %d", &w, &k); w --;
      groupsGrades[groupId[root(w)]][grades[w]] --, groupsGrades[groupId[root(w)]][k] ++;
      grades[w] = k;
    }
  }

  return(0);
}