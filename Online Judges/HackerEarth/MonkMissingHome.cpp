#include <bits/stdc++.h>
#define lli long long int
using namespace std;

/* Tutorial:
  Instead of deletions, go for insertions: reverse the order of the queries.
  For each insertion, you will do a modified DSU merge.
  Since there can be multiple values of a number, each parent will be a map,
  mapping the number to the quantity of occurences.
  So, while merging:
    sum = 0
    for each number i on v:
      for j in [i - d, i + d]:
        if j is in u:
          sum += v[i].occurences * u[j].ocurrences
    And don't forget to merge v to u:
      for each number i on v:
        u[i].occurences += v[i].occurences
*/

const int maxN = 1e5; int n, d;
int a[maxN], order[maxN - 1];
struct Edge { int u, v; };

int parent[maxN];
map<int, lli> parentSet[maxN];
int root(int u)
{
  if (parent[u] < 0) return(u);
  return(parent[u] = root(parent[u]));
}
lli merge(int u, int v)
{
  u = root(u), v = root(v);
  if (u == v) return(0); // never gonna happen
  if (parent[v] < parent[u]) swap(u, v);
  
  lli sum = 0;
  for (auto i: parentSet[v])
    for (int j = i.first - d; j <= i.first + d; j ++)
      if (parentSet[u].count(j))
        sum += parentSet[u][j] * i.second;
  for (auto i: parentSet[v])
  {
    if (!parentSet[u].count(i.first)) parentSet[u][i.first] = 0;
    parentSet[u][i.first] += i.second;
  }
  parentSet[v].clear();
  
  parent[u] += parent[v];
  parent[v] = u;
  return(sum);
}
int setSize(int u)
{
  return(-1 * parent[root(u)]);
}

int main()
{
  memset(parent, -1, sizeof(parent));
  scanf("%d %d", &n, &d);
  for (int i = 0; i < n; i ++)
  {
    scanf("%d", &a[i]);
    parentSet[i][a[i]] = 1;
  }
  Edge edges[n - 1];
  for (int i = 0; i < n - 1; i ++)
  {
    scanf("%d %d", &edges[i].u, &edges[i].v);
    edges[i].u --, edges[i].v --;
  }
  for (int i = 0; i < n - 1; i ++)
  {
    scanf("%d", &order[i]);
    order[i] --;
  }
  reverse(order, order+n-1);

  lli sum = 0;
  vector<lli> ans;
  for (int i = 0; i < n - 1; i ++)
  {
    ans.push_back(sum);
    sum += merge(edges[order[i]].u, edges[order[i]].v);
  }
  reverse(ans.begin(), ans.end());
  for (lli i: ans) printf("%lld\n", i);

  return(0);
}
/*
  It can be done using vector and inplace_merge, it's as fast as, but just because
  the constant is smaller.
  // auto lo = lower_bound(parentSet[u].begin(), parentSet[u].end(), i - d);
  // auto hi = upper_bound(parentSet[u].begin(), parentSet[u].end(), i + d);
  // sum += hi - lo;

  // int prvSize = parentSet[u].size();
  // parentSet[u].insert(parentSet[u].end(), parentSet[v].begin(), parentSet[v].end());
  // inplace_merge(parentSet[u].begin(), parentSet[u].begin()+prvSize, parentSet[u].end());
*/