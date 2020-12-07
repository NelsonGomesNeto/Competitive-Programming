#include <bits/stdc++.h>
using namespace std;

/* Tutorial:
  The core idea is to count how many leafs were wasted
  Do a DFS following these rules:
    If node is maximum: it will carry only the minimum waste possible
    If node is minimum: it will carry every the sum of wastes
    If node if lead: waste == 1
  The answer will be: leafs - wasted leafs + 1
  (+ 1 is just because you will assign numbers starting from 1)
*/

const int maxN = 3e5; int n, leafs;
vector<int> graph[maxN]; bool isMax[maxN];

int dfs(int u, int prv = -1)
{
  if (graph[u].size() == 1 && u) { leafs ++; return(1); }
  int wasted = 0, minimumWaste = 1e7;
  for (int v: graph[u])
    if (v != prv)
    {
      int w = dfs(v, u);
      wasted += w, minimumWaste = min(minimumWaste, w);
    }
  if (isMax[u]) return(minimumWaste); // maximum node can choose the minimum waste
  else return(wasted); // minimum node will waste all nodes below it
}

int main()
{
  scanf("%d", &n);
  for (int i = 0, a; i < n; i ++) { scanf("%d", &a); isMax[i] = a == 1; }
  for (int i = 1, p; i < n; i ++)
  {
    scanf("%d", &p); p --;
    graph[p].push_back(i), graph[i].push_back(p);
  }

  int wastedLeafs = dfs(0);
  printf("%d\n", leafs - wastedLeafs + 1);
  // + 1 just because you fill from 1 to k and to from 0 to k - 1

  return(0);
}