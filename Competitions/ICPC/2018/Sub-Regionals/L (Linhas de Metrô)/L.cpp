#include <bits/stdc++.h>
using namespace std;

/* Tutorial:
  Use LCA to query dist(u, v) in O(lg(n))

  maximum = max(dist(A, C), dist(B, D))
  minimum = min(dist(A, C), dist(B, D))
  if dist(A, B) + dist(C, D) >= minimum
    common = ((maximum - minimum) >> 1) + 1
    divided by two because we're it's counted twice
    + 1 because we're counting vertices and not edges
    Why:
      The maximum will pass through the intersection twice, and the minimum
      will pass (once) through every edge that doesn't belong to the intersection
  else:
    common = 0
    Why:
      The paths A -> B and C -> D must cover the minimum

  (It's easier to understand why if you apply this on images of the problem)
*/

const int maxN = 1e5, maxLog = ceil(log2(1e5)); int n, q, logn;
vector<int> tree[maxN];

int level[maxN], ancestor[maxN][maxLog], logDP[maxN + 1];
void dfs(int u = 0, int prv = -1)
{
  for (int v: tree[u])
    if (v != prv)
    {
      level[v] = level[u] + 1, ancestor[v][0] = u;
      dfs(v, u);
    }
}
void build()
{
  level[0] = ancestor[0][0] = 0; dfs(0);
  for (int i = 1; i < logn; i ++)
    for (int u = 0; u < n; u ++)
      ancestor[u][i] = ancestor[ancestor[u][i - 1]][i - 1];
}
int LCA(int u, int v)
{
  if (level[v] > level[u]) swap(u, v);
  for (int diff = level[u] - level[v], i = 0; diff; diff >>= 1, i ++)
    if (diff & 1)
      u = ancestor[u][i];
  if (u == v) return(u);
  for (int i = logDP[level[u] - 1]; ancestor[u][0] != ancestor[v][0]; i --)
    if (ancestor[u][i] != ancestor[v][i])
      u = ancestor[u][i], v = ancestor[v][i];
  return(ancestor[u][0]);
}
int dist(int a, int b)
{
  return(level[a] + level[b] - 2*level[LCA(a, b)]);
}

int main()
{
  for (int i = 2; i <= maxN; i ++) logDP[i] = logDP[i >> 1] + 1;
  scanf("%d %d", &n, &q); logn = ceil(log2(n));
  for (int i = 0, u, v; i < n - 1; i ++)
  {
    scanf("%d %d", &u, &v); u --, v --;
    tree[u].push_back(v), tree[v].push_back(u);
  }
  build();

  while (q --)
  {
    int a, b, c, d; scanf("%d %d %d %d", &a, &b, &c, &d); a --, b --, c --, d --;
    int ac = dist(a, c), ad = dist(a, d), bc = dist(b, c), bd = dist(b, d), ab = dist(a, b), cd = dist(c, d);
    int maximum = max(ac + bd, ad + bc), minimum = min(ac + bd, ad + bc);
    int common = ((maximum - minimum) >> 1) + 1;
    if (ab + cd < minimum) printf("0\n");
    else printf("%d\n", common);
    // printf("(%d, %d) (%d, %d)\n", a, b, c, d);
    // printf("\tac = %d | ad = %d | bc = %d | bd = %d | maximum = %d | minimum = %d || ab = %d | cd = %d\n", ac, ad, bc, bd, maximum, minimum, ab, cd);
  }
  return(0);
}
