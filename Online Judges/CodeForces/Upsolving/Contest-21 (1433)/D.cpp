#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 5e3; int n;
lli a[maxN];
vector<int> as;

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
int setSize(int u)
{
  return -parent[root(u)];
}

vector<pair<int, int>> edges;

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    as.clear();
    for (int i = 0; i < n; i++)
    {
      scanf("%lld", &a[i]);
      as.push_back(a[i]);
    }

    sort(as.begin(), as.end());
    as.resize(distance(as.begin(), unique(as.begin(), as.end())));

    for (int i = 0; i < n; i++)
      a[i] = lower_bound(as.begin(), as.end(), a[i]) - as.begin();

    for (int i = 0; i < n; i++)
      parent[i] = -1;
    edges.clear();
    for (int i = 0; i < n; i++)
      for (int j = i + 1; j < n; j++)
        if (a[i] != a[j] && root(i) != root(j))
          merge(i, j), edges.push_back({i, j});

    if (setSize(0) == n)
    {
      printf("YES\n");
      for (auto &e: edges)
        printf("%d %d\n", e.first + 1, e.second + 1);
    }
    else
      printf("NO\n");
  }
  return 0;
}