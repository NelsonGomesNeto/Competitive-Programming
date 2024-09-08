#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e2; int n, m;
char mat[maxN][maxN + 1];

int main()
{
  while (scanf("%d %d", &n, &m) != EOF)
  {
    for (int i = 0; i < n; i++)
      scanf(" %s", mat[i]);

    int ans = 0;
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
      {
        if (i + 1 < n)
          ans += mat[i][j] == '.' && mat[i + 1][j] == '.';
        if (j + 1 < m)
          ans += mat[i][j] == '.' && mat[i][j + 1] == '.';
      }
    printf("%d\n", ans);
  }
  return 0;
}