#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
sum(i = [0 : x - 1], a^i) = (a^x - 1) / (a - 1)
A^0, A^0 + A^1, A^0 + A^1 + A^2
sum(x) = sum(i = [0 : x - 1], A^i)
sum(x + 1) = A * sum(x) + A^0
sum(x + 1) = A * sum(x) + 1

A | 1
0 | 1

A^2 | A + 1
0   | 1

A^3 | A^2 + A + 1
0   | 1
*/

lli mod;

vector<vector<lli>> matMult(const vector<vector<lli>>& a, const vector<vector<lli>>& b)
{
  assert(a[0].size() == b.size());
  const int na = a.size(), m = a[0].size(), mb = b[0].size();
  vector<vector<lli>> ans(na, vector<lli>(mb, 0));
  for (int i = 0; i < na; ++i)
    for (int j = 0; j < mb; ++j)
    {
      lli& curr = ans[i][j];
      for (int k = 0; k < m; ++k)
        curr = (curr + a[i][k] * b[k][j] % mod) % mod;
    }
  return ans;
}

vector<vector<lli>> matExp(vector<vector<lli>> x, lli y)
{
  const int n = x.size();
  vector<vector<lli>> ans(n, vector<lli>(n, 0));
  for (int i = 0; i < n; ++i) ans[i][i] = 1;
  while (y)
  {
    if (y & 1) ans = matMult(ans, x);
    x = matMult(x, x), y >>= 1LL;
  }
  return ans;
}

lli a, x;

int main()
{
  while (~scanf("%lld %lld %lld", &a, &x, &mod))
  {
    const vector<vector<lli>> matrixBase{{a, 1}, {0, 1}};
    vector<vector<lli>> ans = matExp(matrixBase, x);
    printf("%lld\n", ans[0][1]);
  }
  return 0;
}
