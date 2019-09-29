#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/* Tutorial:
  There's a simple optimization that will pass in 2 seconds
    O(n²m² + q*n*m)
  But I highly recommend try to optimize to O(n²m² + q) (each querying being O(1))
  Write down the equations, and what each should receive from
  It's BEAUTIFUL
*/

const int maxN = 40 + 1; int n, m, q;
int mat[maxN][maxN], sum[maxN][maxN];
int cnt[maxN][maxN][maxN][maxN];

int getSum(int loi, int loj, int hii, int hij)
{
  return sum[hii][hij] - sum[hii][loj - 1] - sum[loi - 1][hij] + sum[loi - 1][loj - 1];
}

int main()
{
  while (scanf("%d %d %d", &n, &m, &q) != EOF)
  {
    for (int i = 1; i <= n; i ++)
      for (int j = 1; j <= m; j ++)
      {
        scanf("%1d", &mat[i][j]);
        mat[i][j] = !mat[i][j];
        sum[i][j] = mat[i][j] + sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
      }

    for (int i = 1; i <= n; i ++)
      for (int j = 1; j <= m; j ++)
        for (int ii = i; ii <= n; ii ++)
          for (int jj = j; jj <= m; jj ++)
          {
            // printf("%d %d - %d %d - %d\n", i, j, ii, jj, getSum(i, j, ii, jj) == (ii - i + 1) * (jj - j + 1));
            cnt[i][j][ii][jj] = (getSum(i, j, ii, jj) == (ii - i + 1) * (jj - j + 1));
            if (jj - 1 >= j) cnt[i][j][ii][jj] += cnt[i][j][ii][jj - 1];
            if (ii - 1 >= i) cnt[i][j][ii][jj] += cnt[i][j][ii - 1][jj];
            if (ii - 1 >= i && jj - 1 >= j) cnt[i][j][ii][jj] -= cnt[i][j][ii - 1][jj - 1];
          }
    for (int i = n; i >= 1; i --)
      for (int j = m; j >= 1; j --)
        for (int ii = n; ii >= i; ii --)
          for (int jj = m; jj >= j; jj --)
          {
            if (i + 1 <= ii) cnt[i][j][ii][jj] += cnt[i + 1][j][ii][jj];
            if (j + 1 <= jj) cnt[i][j][ii][jj] += cnt[i][j + 1][ii][jj];
            if (i + 1 <= ii && j + 1 <= jj) cnt[i][j][ii][jj] -= cnt[i + 1][j + 1][ii][jj];
          }
    while (q --)
    {
      int loi, loj, hii, hij; scanf("%d %d %d %d", &loi, &loj, &hii, &hij);
      printf("%d\n", cnt[loi][loj][hii][hij]);
    }
  }
  return 0;
}