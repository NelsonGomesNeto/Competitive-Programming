#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 25; int n, m;
int sum[maxN][maxN];
char mat[maxN][maxN + 1];

bool valid(int i, int j, int h, int b)
{
  for (int ii = i; ii < i + h; ii ++)
    for (int jj = j; jj < j + b; jj ++)
      if (mat[ii][jj] == '0')
        return false;
  return true;
}

bool read()
{
  strcpy(mat[n], "");
  scanf("%[^\n]", mat[n]);
  if (strlen(mat[n]) == 0)
    return false;
  n ++;
  getchar();
  return true;
}

int main()
{
  int t; scanf("%d\n\n", &t);
  for (int tt = 0; tt < t; tt ++)
  {
    if (tt) printf("\n");

    n = 0;
    while (read());
    getchar();
    m = strlen(mat[0]);

    for (int i = 0; i < n; i ++)
      for (int j = 0; j < m; j ++)
      {
        sum[i][j] = mat[i][j] == '1';
        if (i) sum[i][j] += sum[i - 1][j];
        if (j) sum[i][j] += sum[i][j - 1];
        if (i && j) sum[i][j] -= sum[i - 1][j - 1];
      }
    int ans = 0;
    for (int i = 0; i < n; i ++)
      for (int j = 0; j < m; j ++)
        for (int h = 1; i + h <= n; h ++)
          for (int b = 1; j + b <= m; b ++)
          {
            int area = 0;
            area = sum[i + h - 1][j + b - 1];
            if (j) area -= sum[i + h - 1][j - 1];
            if (i) area -= sum[i - 1][j + b - 1];
            if (i && j) area += sum[i - 1][j - 1];
            if (area == b*h)
              ans = max(ans, area);
          }
    printf("%d\n", ans);
  }
  return(0);
}