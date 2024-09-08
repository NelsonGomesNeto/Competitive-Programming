#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 8; int n, m;
vector<vector<int>> tgraph, agraph;
vector<pair<int, int>> tedges, aedges;
void readGraph(vector<vector<int>> &graph, vector<pair<int, int>> &edges)
{
  graph.clear(), edges.clear();
  graph.resize(n);
  for (int i = 0; i < m; i++)
  {
    int u, v; scanf("%d %d", &u, &v); u--, v--;
    graph[u].push_back(v), graph[v].push_back(u);
    edges.push_back(make_pair(min(u, v), max(u, v)));
  }
  for (int i = 0; i < n; i++)
    sort(graph[i].begin(), graph[i].end());
}

int main()
{
  while (~scanf("%d %d", &n, &m))
  {
    readGraph(tgraph, tedges);
    readGraph(agraph, aedges);

    vector<int> p; for (int i = 0; i < n; i++) p.push_back(i);
    bool can = false;
    do
    {
      vector<vector<int>> newtgraph;
      newtgraph.clear();
      newtgraph.resize(n);
      for (auto [u, v]: tedges)
      {
        u = p[u], v = p[v];
        newtgraph[u].push_back(v), newtgraph[v].push_back(u);
      }
      for (int i = 0; i < n; i++)
        sort(newtgraph[i].begin(), newtgraph[i].end());

      can |= newtgraph == agraph;
    } while (next_permutation(p.begin(), p.end()));

    printf("%s\n", can ? "Yes" : "No");
  }
  return 0;
}