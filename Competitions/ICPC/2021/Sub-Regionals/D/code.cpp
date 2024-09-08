#include <bits/stdc++.h>
#define DEBUG if(0)
#define ldouble long double
using namespace std;

const int maxN = 5e5;
int side[maxN];

bool isBipartite(vector<int> adj[maxN], vector<int> &nodesToCheck)
{
  queue<int> q;
  // fill(side+from, side+n, -1);

  // DEBUG printf("here %d %d\n", from, n);
  // for (int st = from; st < n; st++) {
  for (int st: nodesToCheck) {
    DEBUG printf("\t%d\n", st);
    for (int u : adj[st]) {
      if (side[u] != -1) {
        if (side[st] != -1 && side[u] == side[st]) return false;
        side[st] = side[u] ^ 1;
      }
    }
    if (side[st] == -1) side[st] = 0;
    q.push(st);

    while (!q.empty()) {
      int v = q.front();
      q.pop();
      DEBUG printf("\t\t%d\n", v);
      for (int u : adj[v]) {
        DEBUG printf("\t\t\t%d\n", u);
        if (side[u] == -1) {
          side[u] = side[v] ^ 1;
          q.push(u);
        } else {
          if (side[u] == side[v])
            return false;
        }
        DEBUG printf("\there %d %d %d\n", st, v, u);
      }
    }
  }

  return true;
}

int n, m;
struct Edge
{
  int u, v; int b;
  void read() { scanf("%d %d %d", &u, &v, &b); u--, v--; }
};
Edge edges[maxN];
vector<int> graph[maxN];
vector<int> currGraph[maxN];
map<int, vector<int>> endPoints;
map<int, vector<Edge>> edgesByColor;
vector<int> possibleColors;
vector<int> ans;
vector<int> allNodes;

void makeUnique(vector<int> &a)
{
  sort(a.begin(), a.end());
  a.resize(distance(a.begin(), unique(a.begin(), a.end())));
}

int main()
{
  int tt = 0;
  while (~scanf("%d %d", &n, &m))
  {
    if (tt++) printf("----------------------\n");
    // graph.clear();
    // graph.resize(n);
    // currGraph.clear();
    // currGraph.resize(n);
    allNodes.clear();
    for (int i = 0; i < n; i++) graph[i].clear(), currGraph[i].clear(), allNodes.push_back(i);
    edgesByColor.clear();
    endPoints.clear();
    possibleColors.clear();
    ans.clear();
    fill(side, side+n, -1);

    for (int i = 0; i < m; i++)
    {
      edges[i].read();
      endPoints[edges[i].b].push_back(edges[i].u);
      endPoints[edges[i].b].push_back(edges[i].v);
      graph[edges[i].u].push_back(edges[i].v);
      graph[edges[i].v].push_back(edges[i].u);
      edgesByColor[edges[i].b].push_back(edges[i]);
    }

    for (auto &p: endPoints)
    {
      makeUnique(p.second);
      if (p.second.size() >= 4)
      {
        possibleColors.push_back(p.first);
        // printf("\t%d %d\n", p.first, (int)p.second.size());
      }
    }
    sort(possibleColors.begin(), possibleColors.end());
    reverse(possibleColors.begin(), possibleColors.end());

    int currV = 0;
    for (auto &c: possibleColors)
    {
      for (auto &e: edgesByColor[c])
      {
        currGraph[e.u].push_back(e.v);
        currGraph[e.v].push_back(e.u);
      }

      bool has[2] = {false, false};
      for (auto &e: edgesByColor[c])
        if ((side[e.u] == side[e.v]) || side[e.u] == -1 || side[e.v] == -1)
          has[max({side[e.u], side[e.v], has[0] + 0})] = true;
      if (has[0] && has[1]) ans.push_back(c);

      bool is = isBipartite(currGraph, endPoints[c]);

      if (!is) break;
    }

    fill(side, side+n, -1);
    if (isBipartite(graph, allNodes)) ans.push_back(0);

    sort(ans.begin(), ans.end());
    for (int a: ans) printf("%d\n", a);
    if (ans.empty()) printf("IMPOSSIBLE\n");
  }
  return 0;
}