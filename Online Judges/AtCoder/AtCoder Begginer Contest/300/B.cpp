#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 30;
int n, m;
char ss[maxN + 1];
vector<string> a, b;

bool equal(const vector<string>& aa, const vector<string>& bb)
{
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      if (aa[i][j] != bb[i][j])
        return false;
  return true;
}

vector<string> transformA(const vector<string>& mat, const int s, const int t)
{
  vector<string> res = mat, tmp = mat;
  for (int j = 0; j < m; ++j)
    for (int i = 0; i < n; ++i)
      res[i][j] = tmp[(i + s) % n][j];
  tmp = res;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      res[i][j] = tmp[i][(j + t) % m];
  return res;
}

vector<string> transformB(const vector<string> &mat, const int s, const int t)
{
  vector<string> res = mat, tmp = mat;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      res[i][j] = tmp[i][(j + t) % m];
  tmp = res;
  for (int j = 0; j < m; ++j)
    for (int i = 0; i < n; ++i)
      res[i][j] = tmp[(i + s) % n][j];
  return res;
}

int main()
{
  while (~scanf("%d %d", &n, &m))
  {
    a.clear();
    a.resize(n);
    for (int i = 0; i < n; ++i)
    {
      scanf(" %s", ss);
      a[i] = string(ss);
    }
    b = a;
    for (int i = 0; i < n; ++i)
    {
      scanf(" %s", ss);
      b[i] = string(ss);
    }

    bool ans = false;
    for (int s = 0; s < n; ++s)
      for (int t = 0; t < m; ++t)
      {
        if (transformA(a, s, t) == b || transformB(a, s, t) == b)
          ans = true;
      }
    printf("%s\n", ans ? "Yes" : "No");
  }
  return 0;
}
