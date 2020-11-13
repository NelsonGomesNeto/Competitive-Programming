#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 50; int n; lli k;
const lli mod = 1e9 + 7;
vector<vector<lli>> graph;

vector<vector<lli>> matrixModMult(vector<vector<lli>> &a, vector<vector<lli>> &b)
{
  int h = a.size(), w = b[0].size(), sz = b.size();
  vector<vector<lli>> ans(h, vector<lli>(w));
  for (int i = 0; i < h; i++)
    for (int j = 0; j < w; j++)
      for (int k = 0; k < sz; k++)
        ans[i][j] = (ans[i][j] + a[i][k] * b[k][j] % mod) % mod;
  return ans;
}
vector<vector<lli>> matrixModPow(vector<vector<lli>> &mat, lli y)
{
  int sz = mat.size();
  vector<vector<lli>> ans(sz, vector<lli>(sz, 0));
  for (int i = 0; i < sz; i++) ans[i][i] = 1;
  vector<vector<lli>> x = mat;

  while (y)
  {
    if (y & 1) ans = matrixModMult(ans, x);
    x = matrixModMult(x, x), y >>= 1LL;
  }

  return ans;
}

int main()
{
  while (scanf("%d %lld", &n, &k) != EOF)
  {
    graph.clear();
    graph.resize(n, vector<lli>(n));
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        scanf("%lld", &graph[i][j]);

    vector<vector<lli>> ans = matrixModPow(graph, k);
    lli sum = 0;
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        sum = (sum + ans[i][j]) % mod;
    printf("%lld\n", sum);
  }
  return 0;
}