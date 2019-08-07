#include <bits/stdc++.h>
using namespace std;
set<int> whole[(int) 1e5];
set<int> now;

void dfs(int a[], int u, int visited[])
{
  now.insert(u);
  if (u != -1) whole[u].insert(now.begin(), now.end());
  if (u == -1) return;
  if (visited[u]) return;
  // visited[u] = 1;
  dfs(a, a[u], visited);
}

int main()
{
  int n, q; scanf("%d %d", &n, &q);
  int a[n]; for (int i = 0; i < n; i ++) scanf("%d", &a[i]);
  int groups = 0, visited[n]; memset(visited, 0, sizeof(visited));
  for (int i = 0; i < n; i ++)
    if (!visited[i])
    {
      now.clear();
      dfs(a, i, visited);
    }

  for (int i = 0; i < q; i ++)
  {
    int x, y; scanf("%d %d", &x, &y);
    printf("%s\n", whole[y].count(x) ? "Yes" : "No");
  }
  return(0);
}