#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n, m;

int parent[maxN];
int root(int u)
{
  return parent[u] < 0 ? u : parent[u] = root(parent[u]);
}
void merge(int u, int v)
{
  if ((u = root(u)) == (v = root(v))) return;
  if (parent[u] > parent[v]) swap(u, v);
  parent[u] += parent[v];
  parent[v] = u;
}

int main()
{
  while (scanf("%d %d", &n, &m) != EOF)
  {
    memset(parent, -1, sizeof(parent));
    for (int i = 0; i < m; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      merge(u, v);
    }

    map<int, set<int>> groups;
    list<list<int>> ans;
    for (int i = 0; i < n; i++)
      groups[root(i)].insert(i);

    while (!groups.empty())
    {
      list<int> now;
      list<int> toRemove;
      for (auto &g: groups)
      {
        now.push_back(*g.second.begin());
        g.second.erase(g.second.begin());
        if (g.second.empty())
          toRemove.push_back(g.first);
      }
      ans.push_back(now);
      for (int i: toRemove)
        groups.erase(i);
    }

    printf("%d\n", (int)ans.size());
  }
  return 0;
}