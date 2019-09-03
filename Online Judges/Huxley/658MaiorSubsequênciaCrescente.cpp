#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 600; int n, m;
int mat[maxN][maxN], rightToLeft[maxN][maxN];

bool fixLimit(int fi, int j, int &limit)
{
  limit = min(limit, rightToLeft[fi + 1][j]);
  while (limit >= j && mat[fi + 1][j] <= mat[fi][limit])
    limit --;
  return limit >= j;
}

int main()
{
  while (scanf("%d %d", &n, &m) != EOF && !(!n && !m))
  {
    for (int i = 0; i < n; i ++)
      for (int j = 0; j < m; j ++)
        scanf("%d", &mat[i][j]);

    for (int i = 0; i < n; i ++)
    {
      rightToLeft[i][m - 1] = m - 1;
      for (int j = m - 2; j >= 0; j --)
        if (mat[i][j] >= mat[i][j + 1])
          rightToLeft[i][j] = j;
        else
          rightToLeft[i][j] = rightToLeft[i][j + 1];
    }

    int ans = 1;
    for (int i = 0; i < n; i ++)
      for (int j = 0; j < m; j ++)
      {
        ans = max(ans, rightToLeft[i][j] - j + 1);
        int fi = i, rightLimit = rightToLeft[i][j];
        while (fi + 1 < n && fixLimit(fi, j, rightLimit))
        {
          fi ++;
          ans = max(ans, (fi - i + 1) * (rightLimit - j + 1));
        }
      }
    printf("%d\n", ans);
  }
  return(0);
}