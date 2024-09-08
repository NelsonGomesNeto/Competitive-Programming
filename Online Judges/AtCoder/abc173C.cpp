#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int n, m, k;
  while (scanf("%d %d %d", &n, &m, &k) != EOF)
  {
    char mat[n][m + 1], aux[n][m + 1];
    for (int i = 0; i < n; i++)
      scanf(" %s", mat[i]);

    memcpy(aux, mat, sizeof(aux));
    int ans = 0;
    for (int bi = 0; bi < (1 << n); bi++)
      for (int bj = 0; bj < (1 << m); bj++)
      {
        memcpy(mat, aux, sizeof(mat));
        for (int i = 0; i < n; i++)
          if ((1 << i) & bi)
            for (int j = 0; j < m; j++)
              mat[i][j] = 'r';
        for (int j = 0; j < m; j++)
          if ((1 << j) & bj)
            for (int i = 0; i < n; i++)
              mat[i][j] = 'r';

        int a = 0;
        for (int i = 0; i < n; i++)
          for (int j = 0; j < m; j++)
            a += mat[i][j] == '#';
        ans += a == k;
      }
    printf("%d\n", ans);
  }
  return 0;
}