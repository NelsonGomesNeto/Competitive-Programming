#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 50; int n;
char mat[maxN][maxN + 1];
char aux[maxN][maxN + 1];
set<string> cnt;

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
      scanf(" %s", mat[i]);

    int minimum = 1e9;
    for (int i = 0; i < n; i++)
    {
      int o = 0, x = 0;
      for (int j = 0; j < n; j++)
        o += mat[i][j] == 'O', x += mat[i][j] == 'X';
      if (o) continue;
      int now = n - x;
      minimum = min(now, minimum);
    }
    for (int j = 0; j < n; j++)
    {
      int o = 0, x = 0;
      for (int i = 0; i < n; i++)
        o += mat[i][j] == 'O', x += mat[i][j] == 'X';
      if (o) continue;
      int now = n - x;
      minimum = min(now, minimum);
    }

    cnt.clear();
    for (int i = 0; i < n; i++)
    {
      int o = 0, x = 0;
      for (int j = 0; j < n; j++)
        o += mat[i][j] == 'O', x += mat[i][j] == 'X';
      if (o) continue;
      int now = n - x;
      if (now == minimum)
      {
        memcpy(aux, mat, sizeof(mat));
        for (int j = 0; j < n; j++)
          aux[i][j] = 'X';
        string result = "";
        for (int i = 0; i < n; i++)
          for (int j = 0; j < n; j++)
            result += aux[i][j];
        cnt.insert(result);
      }
    }
    for (int j = 0; j < n; j++)
    {
      int o = 0, x = 0;
      for (int i = 0; i < n; i++)
        o += mat[i][j] == 'O', x += mat[i][j] == 'X';
      if (o) continue;
      int now = n - x;
      if (now == minimum)
      {
        memcpy(aux, mat, sizeof(mat));
        for (int i = 0; i < n; i++)
          aux[i][j] = 'X';
        string result = "";
        for (int i = 0; i < n; i++)
          for (int j = 0; j < n; j++)
            result += aux[i][j];
        cnt.insert(result);
      }
    }

    if (minimum == 1e9)
      printf("Case #%d: Impossible\n", tt);
    else
      printf("Case #%d: %d %d\n", tt, minimum, (int)cnt.size());
  }
  return 0;
}