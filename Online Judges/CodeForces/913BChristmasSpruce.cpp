#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n; scanf("%d", &n);
  vector<int> graph[n]; int node;

  for (int i = 0; i < n - 1; i ++)
  {
    scanf("%d", &node); node --;
    graph[node].push_back(i + 1);
  }

  int leaf, spruce = 1;
  for (int i = 0; i < n - 1; i ++)
  {
    leaf = 0;
    if (graph[i].size() != 0)
      for (auto u: graph[i])
        if (graph[u].size() == 0) leaf ++;
    if (leaf < 3 && graph[i].size() != 0)
    {
      spruce = 0; break;
    }
  }

  printf("%s\n", spruce ? "Yes" : "No");

  return(0);
}