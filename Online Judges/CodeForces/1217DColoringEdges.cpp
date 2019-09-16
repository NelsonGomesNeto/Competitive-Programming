#include <bits/stdc++.h>
using namespace std;

/* Tutorial:
  It's very important to notice that the answer will be at most 2
  And you can always color the graph using the following rule:
    edgeColor[i] = (u > v)
    Why? Image a cycle as a circle, you will go to the right, but
    always come back from the left, and since all u != v in this cycle:
    there's no order that will make all colors equal

  So, we just need to find if the graph has a cycle
    if it has:
      color the graph as a explained before
    else:
      all colors will be 1
*/

const int maxN = 5e3, maxM = 5e3; int n, m;
int color[maxN], edgeColor[maxN];
vector<int> graph[maxN];

bool dfs(int u = 0)
{
  if (color[u] != 0) return color[u] == 1;
  color[u] = 1;
  for (int v: graph[u])
    if (dfs(v))
      return true;
  color[u] = 2;
  return false;
}

int main()
{
  scanf("%d %d", &n, &m);
  for (int i = 0; i < m; i ++)
  {
    int u, v; scanf("%d %d", &u, &v); u --, v --;
    graph[u].push_back(v);
    edgeColor[i] = (u > v);
  }
  bool hasCycle = false;
  for (int i = 0; i < n; i ++)
    if (color[i] == 0 && dfs(i))
      hasCycle = true;

  if (!hasCycle) memset(edgeColor, 0, sizeof(edgeColor));
  printf("%d\n", hasCycle ? 2 : 1);
  for (int i = 0; i < m; i ++)
    printf("%d%c", edgeColor[i] + 1, i < m - 1 ? ' ' : '\n');

  return 0;
}