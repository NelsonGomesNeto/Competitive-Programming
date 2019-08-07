#include <bits/stdc++.h>
#define lli long long int
using namespace std;

/* Tutorial:
  This problem is exactly the same as Monk Missing Home from HackerEarth
  The only difference is that the range of 'D' is wrong, should be: 0 <= D <= 10
  With that in mind, the solution is easier and done in O(n*lg*D)
  But, here's a different solution with different complexity that works
*/

const int maxN = 1e5; int n, d;
int a[maxN], order[maxN - 1];
struct Edge { int u, v; };

int parent[maxN];
vector<int> parentSet[maxN];
int root(int u)
{
  if (parent[u] < 0) return(u);
  return(parent[u] = root(parent[u]));
}
lli merge(int u, int v)
{
  u = root(u), v = root(v);
  if (u == v) return(0); // never gonna happen
  if (parent[v] < parent[u]) swap(parent[u], parent[v]), swap(parentSet[u], parentSet[v]);
  lli sum = 0;
  for (int i: parentSet[v])
  {
    auto lo = lower_bound(parentSet[u].begin(), parentSet[u].end(), i - d);
    auto hi = upper_bound(parentSet[u].begin(), parentSet[u].end(), i + d);
    sum += hi - lo;
  }
  int prvSize = parentSet[u].size();
  parentSet[u].insert(parentSet[u].end(), parentSet[v].begin(), parentSet[v].end());
  inplace_merge(parentSet[u].begin(), parentSet[u].begin()+prvSize, parentSet[u].end());
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
    parentSet[i].push_back(a[i]);
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