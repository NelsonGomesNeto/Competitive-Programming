#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/* Tutorial:
  The core of this problem is very similiar to Knapsack, except that the value of
  all items are 1. Since you only need to worry about the "weight" of them.
  This version of the problem can be solved easily in O(n^2) using DP:
  fill(memo, inf)
  for (int i = 0; i < n; i++)
    for (int k = 0; k <= i + 1; k++)
      memo[i][k] = min({memo[i][k], memo[i - 1][k], memo[i - 1][k - 1] + w[i]});

*/

const int maxN = 5e3; int n; lli b;
const lli inf = 1e12;
vector<int> tree[maxN]; int subtreeSize[maxN];
lli c[maxN], d[maxN];

// memo(i, u, k) = minimum cost to buy k items from u's subtree (i represents if using discounts are allowed)
lli memo[2][maxN][maxN + 1];
void dfs(int u = 0)
{
  memo[0][u][1] = c[u], memo[1][u][1] = c[u] - d[u], memo[0][u][0] = 0;
  subtreeSize[u] = 1;

  for (int v: tree[u])
  {
    dfs(v);
    for (int j = subtreeSize[u]; j >= 0; j--)
      for (int k = 0; k <= subtreeSize[v]; k++)
      {
        memo[0][u][j + k] = min(memo[0][u][j + k], memo[0][u][j] + memo[0][v][k]);
        memo[1][u][j + k] = min(memo[1][u][j + k], memo[1][u][j] + min(memo[0][v][k], memo[1][v][k]));
      }
    subtreeSize[u] += subtreeSize[v];
  }
}

int main()
{
  while (scanf("%d %lld", &n, &b) != EOF)
  {
    for (int i = 0; i < n; i++) tree[i].clear();

    scanf("%lld %lld", &c[0], &d[0]);
    for (int i = 1; i < n; i++)
    {
      int p; scanf("%lld %lld %d", &c[i], &d[i], &p); p--;
      tree[p].push_back(i);
    }

    for (int i = 0; i < 2; i++)
      for (int u = 0; u < n; u++)
        for (int k = 0; k <= n; k++)
          memo[i][u][k] = inf;
    dfs();

    int ans = 0;
    for (int k = 1; k <= n; k++)
      if (min(memo[0][0][k], memo[1][0][k]) <= b)
        ans = k;

    printf("%d\n", ans);
  }
  return 0;
}