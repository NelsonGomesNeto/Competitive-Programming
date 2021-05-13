#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/* Tutorial:
  At any time, there's a 1 / m probability for every edge.

  Remeber that the expected value is equal to: sum all (case / probability)

  Let's first try to understand what happens with a single iteration:
    Let's look the probability contribution of every vertex on 'u':
      u it self:
        It will start at 1 (fully likely), and decrease 1 / (2*m) for every connected vertex
        selfContribution = 1 - connectedVertices[u] / 2*m
      other vertices:
        otherContribution = {
          0, if the vertex isn't connected
          1 / (2*m), if the vertex is conneted
        }
    We can represent that with a matrix:
      probabilityContribution[i][j] is the probability contribution of vertex 'i' on
      vertex 'j'

  So the answer is: a * probabilityContribution^k

  BEAUTIFUL
*/

const int maxN = 100; int n, m; lli k;
const lli mod = 1e9 + 7;
vector<vector<lli>> a;
vector<int> graph[maxN];

void printMatrix(vector<vector<lli>> &mat)
{
  for (int i = 0; i < mat.size(); i++)
    for (int j = 0; j < mat[0].size(); j++)
      printf("%10lld%c", mat[i][j], j < mat[0].size() - 1 ? ' ' : '\n');
}

vector<vector<lli>> matrixModMult(vector<vector<lli>> &x, vector<vector<lli>> &y)
{
  assert(x[0].size() == y.size());

  vector<vector<lli>> ans(x.size(), vector<lli>(y[0].size(), 0));
  for (int i = 0; i < x.size(); i++)
    for (int j = 0; j < y[0].size(); j++)
      for (int k = 0; k < y.size(); k++)
        ans[i][j] = (ans[i][j] + x[i][k] * y[k][j] % mod + mod) % mod;

  return ans;
}

vector<vector<lli>> matrixModPow(vector<vector<lli>> x, lli y)
{
  assert(x.size() == x[0].size());

  vector<vector<lli>> ans(x.size(), vector<lli>(x[0].size(), 0));
  for (int i = 0; i < ans.size(); i++) ans[i][i] = 1;
  while (y)
  {
    if (y & 1LL) ans = matrixModMult(ans, x);
    x = matrixModMult(x, x), y >>= 1LL;
  }
  return ans;
}

lli modPow(lli x, lli y)
{
  lli ans = 1;
  while (y)
  {
    if (y & 1LL) ans = ans * x % mod;
    x = x * x % mod, y >>= 1LL;
  }
  return ans;
}

lli inv(lli x)
{
  return modPow(x, mod - 2);
}

int main()
{
  while (~scanf("%d %d %lld", &n, &m, &k))
  {
    for (int i = 0; i < n; i++)
      graph[i].clear();

    a.clear(); a.resize(1, vector<lli>(n));
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[0][i]);

    for (int i = 0; i < m; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      graph[u].push_back(v), graph[v].push_back(u);
    }

    vector<vector<lli>> contributionMatrix(n, vector<lli>(n, 0));
    for (int u = 0; u < n; u++)
    {
      int d = graph[u].size();
      contributionMatrix[u][u] = (1 - d * inv(2*m) % mod + mod) % mod;
      for (int v: graph[u])
        contributionMatrix[v][u] = 1 * inv(2*m) % mod;
    }

    contributionMatrix = matrixModPow(contributionMatrix, k);

    vector<vector<lli>> ans = matrixModMult(a, contributionMatrix);
    for (int i = 0; i < n; i++)
      printf("%lld\n", ans[0][i]);
  }
  return 0;
}