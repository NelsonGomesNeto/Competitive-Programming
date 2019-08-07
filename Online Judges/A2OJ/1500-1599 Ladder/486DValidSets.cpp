#include <bits/stdc++.h>
#define lli long long int
using namespace std;

/* Tutorial:
The calculation for d = inf is the following:
  dfs(u):
    ans = 1
    for every adjacent vertex v: // of course, ignore the previous vertex
      ans *= dfs(v) + 1
    return(ans)
To convert that for any d, we just need to add an if to avoid
the vertices that exceeds the range. For every vertex, mark it
as root and visit only vertices where a[root] <= a[v] <= a[root] + d
Yes, a[root] is the minimum and a[root] + d is the maximum, pretty neat
for every vertex u:
  ans += dfsWithIf(u, u) // (currentNode, rootNode)

The only worry now is to avoid duplicate couting:
if (a[v] == a[root] && v < root) continue;
They have the same value, so, if they met, they sure will met twice
So, you count only for the one with a lower index (or higher, it doesn't matter)
*/

const int maxN = 2e3; int d, n;
const lli mod = 1e9 + 7;
vector<int> graph[maxN]; int a[maxN];

lli dfs(int u = 0, int prv = -1, int root = 0)
{
  lli ans = 1;
  for (int v: graph[u])
  {
    if (v == prv) continue;
    if (a[v] < a[root] || a[v] > a[root] + d) continue;
    if (a[v] == a[root] && v < root) continue;
    ans = (ans * (dfs(v, u, root) + 1)) % mod;
  }
  return(ans);
}

int main()
{
  scanf("%d %d", &d, &n);
  for (int i = 0; i < n; i ++) scanf("%d", &a[i]);
  for (int i = 0, u, v; i < n - 1; i ++)
  {
    scanf("%d %d", &u, &v); u --, v --;
    graph[u].push_back(v), graph[v].push_back(u);
  }

  lli ans = 0;
  for (int i = 0; i < n; i ++)
    ans = (ans + dfs(i, -1, i)) % mod;
  printf("%lld\n", ans);

  return(0);
}