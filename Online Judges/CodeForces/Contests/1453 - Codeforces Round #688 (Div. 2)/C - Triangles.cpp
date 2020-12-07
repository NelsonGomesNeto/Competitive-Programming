#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e3; int n;
char mat[maxN][maxN + 1];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
      scanf(" %s", mat[i]);

    lli ans[256];
    int firstRow[256], lastRow[256], firstColumn[256], lastColumn[256];
    memset(firstRow, -1, sizeof(firstRow));
    memset(lastRow, -1, sizeof(lastRow));
    memset(firstColumn, -1, sizeof(firstColumn));
    memset(lastColumn, -1, sizeof(lastColumn));

    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
      {
        char d = mat[i][j];
        if (firstRow[d] == -1 || i < firstRow[d]) firstRow[d] = i;
        if (lastRow[d] == -1 || i > lastRow[d]) lastRow[d] = i;
        if (firstColumn[d] == -1 || j < firstColumn[d]) firstColumn[d] = j;
        if (lastColumn[d] == -1 || j > lastColumn[d]) lastColumn[d] = j;
      }

    memset(ans, 0, sizeof(ans));
    for (char d = '0'; d <= '9'; d++)
    {
      for (int i = 0; i < n; i++)
      {
        int lo = 0, hi = n - 1;
        while (lo < n && mat[i][lo] != d) lo++;
        while (hi >= 0 && mat[i][hi] != d) hi--;

        if (lo <= hi)
        {
          ans[d] = max(ans[d], (lli)(hi - lo) * max(i, n - i - 1));
          lli base = max(n - lo - 1, hi);
          ans[d] = max({ans[d], base * (i - firstRow[d]), base * (lastRow[d] - i)});
        }
      }

      for (int j = 0; j < n; j++)
      {
        int lo = 0, hi = n - 1;
        while (lo < n && mat[lo][j] != d) lo++;
        while (hi >= 0 && mat[hi][j] != d) hi--;

        if (lo <= hi)
        {
          ans[d] = max(ans[d], (lli)(hi - lo) * max(j, n - j - 1));
          lli base = max(n - lo - 1, hi);
          ans[d] = max({ans[d], base * (j - firstColumn[d]), base * (lastColumn[d] - j)});
        }
      }
    }

    for (char d = '0'; d <= '9'; d++)
      printf("%lld%c", ans[d], d < '9' ? ' ' : '\n');
  }
  return 0;
}