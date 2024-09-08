#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100; int n, m, x, y;
char mat[maxN][maxN + 1];

int di[4] = {0, 0, -1, 1}, dj[4] = {1, -1, 0, 0};
int main()
{
  while (~scanf("%d %d %d %d", &n, &m, &x, &y))
  {
    x--, y--;
    for (int i = 0; i < n; i++)
      scanf(" %s", mat[i]);

    int ans = -3;
    for (int k = 0; k < 4; k++)
    {
      int i = x, j = y;
      while (i >= 0 && i < n && j >= 0 && j < m && mat[i][j] == '.')
      {
        i += di[k], j += dj[k];
        ans++;
      }
    }
    ans = max(ans, 0);

    printf("%d\n", ans);
  }
  return 0;
}