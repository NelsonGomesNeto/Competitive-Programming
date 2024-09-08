#include <bits/stdc++.h>
#define DEBUG if(1)
#define lli long long int
#define ldouble long double
using namespace std;

struct DSU
{
  int size;
  vector<int> parents;
  DSU() { parents.clear(); }
  DSU(int sz) : size(sz) { init(); }
  void init() { parents.resize(size, -1); }
  int root(int u) { return parents[u] < 0 ? u : parents[u] = root(parents[u]); }
  void merge(int u, int v)
  {
    u = root(u), v = root(v);
    if (u == v) return;
    if (parents[u] > parents[v]) swap(u, v);
    parents[u] += parents[v];
    parents[v] = u;
  }
  int setSize(int u) { return -parents[root(u)]; }
  bool sameSet(int u, int v) { return root(u) == root(v); }
};
DSU dsu;

const int maxN = 2e3; int n;
vector<int> tree[maxN + 1];
vector<pair<int, int>> ans;

int d[maxN][maxN + 1];
bool done[maxN + 1], queried[maxN + 1];
int height[maxN + 1];
int unqueriedBelow[maxN + 1];

void addEdge(int u, int v)
{
  tree[u].push_back(v), tree[v].push_back(u), dsu.merge(u, v);
  ans.push_back({u, v}), done[u] = done[v] = true;
}

void dfs(int u = 1, int prv = -1, int depth = 0)
{
  height[u] = depth;
  for (int v: tree[u])
    if (v != prv)
      dfs(v, u, depth + 1);
}

int main()
{
  scanf("%d", &n);

  dsu = DSU(n + 1);
  dsu.init();

  priority_queue<pair<int, int>> q;
  int queries = n >> 1;
  int furthest = 0;
  int now = 3;
  while (queries)
  {
    for (int i = 1; i <= n; i++)
      if (!done[i])
      {
        q.push({0, i});
        break;
      }

    while (!q.empty() && queries)
    {
      int u = q.top().second; q.pop();
      // if (u != 1 && dsu.sameSet(1, u)) done[u] = true;
      if (done[u]) continue;
      done[u] = true;

      queries--, queried[u] = true;
      printf("? %d\n", u); fflush(stdout);
      for (int v = 1; v <= n; v++)
      {
        scanf("%d", &d[u][v]);
        furthest = max(furthest, d[u][v]);
      }

      for (int v = 1; v <= n; v++)
      {
        if (d[u][v] == 1) //|| (u != 1 && droot[u] + d[v] == d[v]))
          addEdge(u, v);
        else if (d[u][v] == now && !done[v])
          q.push({d[u][v], v});
      }
    }
    now--;
  }

  // dfs();

  // vector<pair<int, pair<int, int>>> pendings;
  // for (int i = 1; i <= n; i++)
  //   if (!done[i])
  //   {
  //     int minDist = n, minHeight = n, jj = -1;
  //     for (int j = 1; j <= n; j++)
  //       if (done[j] && d[j][i])
  //       {
  //         if (d[j][i] < minDist || (d[j][i] == minDist && height[j] < minHeight))
  //           minDist = d[j][i], minHeight = height[j], jj = j;
  //       }
  //     pendings.push_back({minDist, {i, jj}});
  //   }
  // sort(pendings.begin(), pendings.end());
  // DEBUG printf("# %d\n", (int)pendings.size()); fflush(stdout);
  // for (auto &p: pendings)
  // {
  //   int u = p.second.first;
  //   if (p.first == 2)
  //   {
  //     int vv = -1;
  //     for (int v: tree[p.second.second])
  //       if (!queried[v] && height[v] > height[p.second.second])
  //         vv = v;

  //     int v = vv;
  //     DEBUG printf("# trying: %d %d | %d\n", u, v, height[v]);
  //     addEdge(u, v);
  //     unqueriedBelow[p.second.second] = u;
  //   }
  //   else
  //   {
  //     int v = unqueriedBelow[p.second.second];
  //     addEdge(u, v);
  //     unqueriedBelow[p.second.second] = u;
  //   }
  //   DEBUG printf("# %d %d %d\n", p.first, p.second.first, p.second.second); fflush(stdout);
  // }

  printf("!\n");
  for (auto &[u, v]: ans)
    printf("%d %d\n", u, v);
  fflush(stdout);

  return 0;
}
