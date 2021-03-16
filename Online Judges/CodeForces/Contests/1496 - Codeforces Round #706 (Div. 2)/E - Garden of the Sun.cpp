#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 5e2; int n, m;
char mat[maxN][maxN + 1];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
      scanf(" %s", mat[i]);

    int base = (m % 3 == 0 || m % 3 == 2) ? 1 : 0;

    for (int j = base; j < m; j += 3)
      for (int i = 0; i < n; i++)
        mat[i][j] = 'X';

    for (int j = base + 1; j + 1 < m; j += 3)
    {
      bool done = false;
      if (!done)
        for (int i = 0; i < n; i++)
          if (mat[i][j] == 'X' || mat[i][j + 1] == 'X')
          {
            mat[i][j] = mat[i][j + 1] = 'X';
            done = true;
            break;
          }

      if (!done)
        mat[0][j] = mat[0][j + 1] = 'X';
    }

    for (int i = 0; i < n; i++)
      printf("%s\n", mat[i]);

  }
  return 0;
}
