#include <bits/stcd++.h>
using namespace std;
const int maxN = 1e5;

class Solution
{
public:
  bool removed[4 * maxN];
  int parent[2][maxN];
  int root(int k, int u)
  {
    return parent[k][u] < 0 ? u : parent[k][u] = root(k, parent[k][u]);
  }
  void merge(int k, int u, int v)
  {
    if ((u = root(k, u)) == (v = root(k, v)))
      return;
    if (parent[k][u] > parent[k][v])
      swap(u, v);
    parent[k][u] += parent[k][v];
    parent[k][v] = u;
  }
  int setSize(int k, int u)
  {
    return -parent[k][root(k, u)];
  }

  int maxNumEdgesToRemove(int n, vector<vector<int>> &edges)
  {
    memset(parent, -1, sizeof(parent));
    memset(removed, false, sizeof(removed));

    for (int i = 0; i < edges.size(); i++)
      edges[i][1]--, edges[i][2]--;

    for (int i = 0; i < edges.size(); i++)
    {
      int u = edges[i][1], v = edges[i][2];
      if (edges[i][0] == 3)
      {
        if (root(1, u) == root(1, v))
          removed[i] = true;
        else
          merge(0, u, v), merge(1, u, v);
      }
    }

    for (int i = 0; i < edges.size(); i++)
    {
      if (removed[i])
        continue;
      int u = edges[i][1], v = edges[i][2];
      for (int j = 0; j < 2; j++)
      {
        if (edges[i][0] == j + 1)
        {
          if (root(j, u) == root(j, v))
            removed[i] = true;
          else
            merge(j, u, v);
        }
      }
    }

    bool can = setSize(0, 0) == n && setSize(1, 0) == n;
    int ans = 0;
    for (int i = 0; i < edges.size(); i++)
      ans += removed[i];

    return can ? ans : -1;
  }
};