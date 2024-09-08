#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100;
int n;

bool match(vector<vector<int>> &a, vector<vector<int>> &b)
{
  bool ans = true;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      if (a[i][j] && !b[i][j])
        ans = false;
  return ans;
}

vector<vector<int>> a, b;

void rotate(vector<vector<int>>& mat)
{
  auto temp = mat;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      mat[i][j] = temp[n - j - 1][i];
}

int main()
{
  while (~scanf("%d", &n))
  {
    a.clear();
    a.resize(n, vector<int>(n));
    b = a;
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        scanf("%d", &a[i][j]);
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        scanf("%d", &b[i][j]);

    bool ans = false;
    for (int r = 0; r < 4; ++r)
    {
      ans |= match(a, b);
      rotate(b);
    }
    printf("%s\n", ans ? "Yes" : "No");
  }
  return 0;
}
