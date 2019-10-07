#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/* Tutorial:
  For each vertex, you can choose at most k edges to add to the answer (and you
  can't add the same edge twice). Formally, for each vertex u, you either choose
  or not the edge(u, parent[u]).

  Using dfs and DP we can calculate memo[u][false] and memo[u][true] for all u
  childsAns = {memo[v][true] + uv.cost - memo[v][false] for all childs of u}
  Sort childsAns descendelly
  We can choose (k - chose) edges, so:
    memo[u][chose] = max(sum(memo[v][false]),
                         sum(memo[v][false]) + childsAns[0 : i] for i in [0 : k - chose))
*/

const int maxN = 5e5; int n, k;
struct Edge { int to; lli cost; };
vector<Edge> graph[maxN];

lli memo[maxN][2];
lli dfs(int u = 0, int prv = -1, bool chose = false)
{
  if (memo[u][chose] == -1)
  {
    vector<lli> childAns;
    lli sum = 0;
    for (Edge &e: graph[u])
    {
      if (e.to == prv) continue;
      childAns.push_back(dfs(e.to, u, true) + e.cost - dfs(e.to, u, false));
      sum += memo[e.to][false];
    }
    sort(childAns.begin(), childAns.end(), greater<lli>());

    memo[u][chose] = sum;
    for (int i = 0; i < k - chose && i < childAns.size(); i ++)
    {
      sum += childAns[i];
      memo[u][chose] = max(memo[u][chose], sum);
    }
  }
  return memo[u][chose];
}

int main()
{
  int q; scanf("%d", &q);
  while (q --)
  {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i ++) graph[i].clear(), memo[i][0] = memo[i][1] = -1;
    for (int i = 0; i < n - 1; i ++)
    {
      int u, v; lli w; scanf("%d %d %lld", &u, &v, &w); u --, v --;
      graph[u].push_back({v, w}), graph[v].push_back({u, w});
    }

    lli ans = dfs();
    DEBUG for (int i = 0; i < n; i ++)
      printf("%d %lld %lld\n", i + 1, memo[i][0], memo[i][1]);
    printf("%lld\n", ans);
  }
  return 0;
}
