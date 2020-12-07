#include <bits/stdc++.h>
#define lli long long int
using namespace std;

/* Tutorial:
  We will use DSU, and keep track of the size of each set

  Sort all edges by the weight (ascending)
  For each query, iterate through the edges while edge.w <= qi
    With DSU, we know the size of each set from the current edge's vertices
    So ans += choose(uSet.size + vSet.size, 2) - choose(uSet.size, 2) - choose(vSet.size, 2)
      choose(x, 2) == x * (x - 1) / 2, which is to calculate the amount of paths from anyone
      to anyone (yes, a complete graph :))
    Memo the answer and also keep track of the current edge, so you don't need to iterate from
    the beginning again
*/

const int maxN = 2e5; int n, q;
int parent[maxN];
int root(int u)
{
  return parent[u] < 0 ? u : parent[u] = root(parent[u]);
}
bool sameSet(int u, int v)
{
  return root(u) == root(v);
}
void merge(int u, int v)
{
  if ((u = root(u)) == (v = root(v))) return;
  if (parent[u] > parent[v]) swap(u, v);
  parent[u] += parent[v];
  parent[v] = u;
}
lli setSize(int u)
{
  return -parent[root(u)];
}
vector<pair<int, pair<int, int>>> edges; int it;
lli memo[maxN + 1];

// Calculates the amount of paths of the set, given it's size
// The formula is from the amount of edges of a complete graph ;)
lli pathsCount(lli sz)
{
  return sz * (sz - 1) >> 1LL;
}
void mergeAll(int w)
{
  for (; it < edges.size() && edges[it].first <= w; it ++)
  {
    if (memo[edges[it].first] == -1)
    {
      int j;
      for (j = edges[it].first - 1; j > 0 && memo[j] == -1; j --);
      while (++ j <= edges[it].first) memo[j] = memo[j - 1];
    }
    if (!sameSet(edges[it].second.first, edges[it].second.second))
    {
      lli s1 = setSize(edges[it].second.first), s2 = setSize(edges[it].second.second);
      memo[edges[it].first] += pathsCount(s1 + s2) - pathsCount(s1) - pathsCount(s2);
      merge(edges[it].second.first, edges[it].second.second);
    }
  }
  int j;
  for (j = w; j > 0 && memo[j] == -1; j --);
  while (++ j <= w) memo[j] = memo[j - 1];
}

int main()
{
  memset(parent, -1, sizeof(parent));
  scanf("%d %d", &n, &q);
  for (int i = 0; i < n - 1; i ++)
  {
    int u, v, c; scanf("%d %d %d", &u, &v, &c); u --, v --;
    edges.push_back({c, {u, v}});
  }
  sort(edges.begin(), edges.end());

  memset(memo, -1, sizeof(memo));
  memo[0] = 0;
  while (q --)
  {
    int qi; scanf("%d", &qi);
    if (memo[qi] == -1) mergeAll(qi);
    printf("%lld ", memo[qi]);
  }
  printf("\n");

  return(0);
}