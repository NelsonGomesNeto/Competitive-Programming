#include <bits/stdc++.h>
using namespace std;
const int size = 10001;
int cities, capacity;
int debts[size], parent[size], visited[size];

int dfs(vector<pair<int, int> > graph[], int u, int cost, int dad)
{
  int travel = 0;
  visited[u] = 1;
  for (auto v: graph[u])
    if (!visited[v.first])
      travel += dfs(graph, v.first, v.second, u);

  travel += 2 * ((debts[u] / capacity) + (debts[u] % capacity > 0)) * cost;
  debts[dad] += debts[u];

  return(travel);
}

int main()
{
  scanf("%d %d", &cities, &capacity);
  for (int i = 0; i < cities; i ++) scanf("%d", &debts[i]);

  vector<pair<int, int> > graph[cities];
  int u, v, c;
  for (int i = 0; i < cities - 1; i ++)
  {
    scanf("%d %d %d", &u, &v, &c); u --; v --;
    graph[u].push_back({v, c});
    graph[v].push_back({u, c});
  }

  memset(visited, 0, sizeof(visited));
  int ans = dfs(graph, 0, 0, 0);

  printf("%d\n", ans);

  return(0);
}