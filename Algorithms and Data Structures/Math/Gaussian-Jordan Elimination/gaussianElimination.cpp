#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const double eps = 1e-12;
int gauss(vector<vector<double>> a, vector<double> &ans)
{
  int n = a.size(), m = a[0].size() - 1;

  vector<int> where(m, - 1);
  for (int col = 0, row = 0; col < m && row < n; col++)
  {
    int sel = row;
    for (int i = row; i < n; i++)
      if (abs(a[i][col]) > abs(a[sel][col]))
        sel = i;

    if (abs(a[sel][col]) < eps)
      continue;

    for (int j = col; j <= m; j++)
      swap(a[sel][j], a[row][j]);
    where[col] = row;

    for (int i = 0; i < n; i++)
      if (i != row)
      {
        double c = a[i][col] / a[row][col];
        for (int j = col; j <= m; j++)
          a[i][j] -= a[row][j] * c;
      }

    row++;
  }

  ans.resize(m, 0);
  for (int i = 0; i < m; i++)
    if (where[i] != -1)
      ans[i] = a[where[i]][m] / a[where[i]][i];
  for (int i = 0; i < n; i++)
  {
    double sum = 0;
    for (int j = 0; j < m; j++)
      sum += ans[j] * a[i][j];
    if (abs(sum - a[i][m]) > eps)
      return 0;
  }

  for (int i= 0; i < m; i++)
    if (where[i] == -1)
      return 2;
  return 1;
}

const int maxN = 1e2; int n, m;
vector<vector<double>> mat;
vector<double> ans;

int main()
{
  while (scanf("%d %d", &n, &m) != EOF)
  {
    mat.resize(n, vector<double>(m + 1));
    for (int i = 0; i < n; i++)
      for (int j = 0; j <= m; j++)
        scanf("%lf", &mat[i][j]);

    int solutions = gauss(mat, ans);
    printf("Solutions: %s\n", solutions == 0 ? "ZERO" : solutions == 1 ? "ONE" : "INF");
    for (int i = 0; i < m; i++)
      printf("x_%d: %lf\n", i, ans[i]);
  }
  return 0;
}