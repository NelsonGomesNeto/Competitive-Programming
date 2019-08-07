#include <bits/stdc++.h>
using namespace std;

/* Tutorial:
  nodes compatible with u = indegree[u]
  nodes imcompatible with u = setSize - 1 - indegree[u]
*/

const int maxN = 1e5; int n, m, A, B;
set<int> graph[maxN];
set<pair<int, int>> chosen;
int indegree[maxN];
bool inside[maxN];

int main()
{
  scanf("%d %d %d %d", &n, &m, &A, &B);
  for (int i = 0, u, v; i < m; i ++)
  {
    scanf("%d %d", &u, &v); u --, v --;
    graph[u].insert(v), graph[v].insert({u});
    indegree[u] ++, indegree[v] ++;
  }

  for (int i = 0; i < n; i ++)
  {
    chosen.insert({indegree[i], i});
    inside[i] = true;
  }

  bool allValid = false;
  while (!allValid && !chosen.empty())
  {
    allValid = true;
    for (int left = 0; left < 2 && !chosen.empty(); left ++)
    {
      int u = (left == 0) ? chosen.begin()->second : chosen.rbegin()->second;
      if (indegree[u] >= A && (chosen.size() - 1 - indegree[u]) >= B) continue;
      allValid = false;
      chosen.erase({indegree[u], u}), inside[u] = false;
      for (int v: graph[u])
        if (inside[v])
        {
          chosen.erase({indegree[v], v});
          graph[v].erase(u);
          chosen.insert({-- indegree[v], v});
        }
    }
  }

  printf("%d\n", (int) chosen.size());

  return(0);
}