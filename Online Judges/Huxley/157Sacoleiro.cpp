#include <bits/stdc++.h>
using namespace std;
int n, t;

int main()
{
  scanf("%d %d", &n, &t);
  vector<vector<int> > graph[n];
  for (int i = 0; i < n; i ++)
  {
    int u, v, c, e; char group;
    scanf("%d %d %c %d", &u, &c, &group, &e);
    for (int j = 0; j < e; j ++)
    {
      scanf("%d", &v);
      graph[u].push_back({v, c, group});
    }
  }

  int ans = dfs()
  return(0);
}
