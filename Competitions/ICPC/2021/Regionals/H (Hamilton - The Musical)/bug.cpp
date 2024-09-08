#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 1005
#define mod 998244353
#define INF 1e18

namespace mcf
{
  struct edge
  {
    int to, capacity, cost, res;
  };

  int source, destiny;
  vector<edge> adj[MAXN];
  vector<int> dist;
  vector<int> parent;
  vector<int> edge_index;
  vector<bool> in_queue;

  void add_edge(int a, int b, int c, int d)
  {
    adj[a].pb({b, c, d, (int)adj[b].size()});
    adj[b].pb({a, 0, -d, (int)adj[a].size() - 1});
  }
  bool dijkstra(int s)
  {
    dist.assign(MAXN, INF);
    parent.assign(MAXN, -1);
    edge_index.assign(MAXN, -1);
    in_queue.assign(MAXN, false);
    dist[s] = 0;
    queue<int> q;
    q.push(s);
    while (!q.empty())
    {
      int u = q.front(), idx = 0;
      q.pop();
      in_queue[u] = false;
      for (auto const &v : adj[u])
      {
        if (v.capacity && dist[v.to] > dist[u] + v.cost)
        {
          dist[v.to] = dist[u] + v.cost;
          parent[v.to] = u;
          edge_index[v.to] = idx;
          if (!in_queue[v.to])
          {
            in_queue[v.to] = true;
            q.push(v.to);
          }
        }
        idx++;
      }
    }
    return dist[destiny] != INF;
  }
  int get_cost()
  {
    int flow = 0, cost = 0;
    while (dijkstra(source))
    {
      int curr_flow = INF, curr = destiny;
      while (curr != source)
      {
        int p = parent[curr];
        curr_flow = min(curr_flow, adj[p][edge_index[curr]].capacity);
        curr = p;
      }
      flow += curr_flow;
      cost += curr_flow * dist[destiny];
      curr = destiny;
      while (curr != source)
      {
        int p = parent[curr];
        int res_idx = adj[p][edge_index[curr]].res;
        adj[p][edge_index[curr]].capacity -= curr_flow;
        adj[curr][res_idx].capacity += curr_flow;
        curr = p;
      }
    }
    return cost;
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  vector<vector<int>> c(n + 1, vector<int>(n + 1));
  for (int i = 1; i <= n; i++)
  {
    for (int j = 1; j <= n; j++)
      cin >> c[i][j];
  }
  int sz = (n + 1) >> 1;
  mcf::source = 998, mcf::destiny = 999;
  for (int i = 0; i < sz; i++)
    mcf::add_edge(mcf::source, i, 1, 0);
  for (int i = sz; i < sz + sz; i++)
    mcf::add_edge(i, mcf::destiny, 1, 0);
  for (int i = 1; i <= n; i += 2)
  {
    for (int j = 2; j <= n; j += 2)
    {
      int cc = c[i][j];
      if (j - 2 >= 0)
        cc += c[j - 2][i];
      mcf::add_edge(i / 2, sz + ((j - 1) / 2), 1, cc);
    }
    // if (n & 1)
    //   mcf::add_edge(i / 2, sz + sz - 1, 1, c[n - 1][i]);
  }
  cout << mcf::get_cost() << endl;
  return 0;
}