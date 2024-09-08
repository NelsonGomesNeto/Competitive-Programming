#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 500; int n;
int s[maxN], t[maxN];
lli u[maxN], v[maxN];

lli mat[maxN][maxN];

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i++) scanf("%d", &s[i]);
    for (int i = 0; i < n; i++) scanf("%d", &t[i]);
    for (int i = 0; i < n; i++) scanf("%lld", &u[i]);
    for (int i = 0; i < n; i++) scanf("%lld", &v[i]);

    bool can = true;
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        mat[i][j] = u[i] | v[j];

    for (int k = 0; k < n; k++)
    {
      for (int i = 0; i < n; i++)
      {
        lli now = mat[i][0];
        for (int j = 1; j < n; j++)
          now = (s[i] ? now | mat[i][j] : now & mat[i][j]);
        if (now != u[i])
        {
          DEBUG printf("row %d %d %lld %lld\n", i, s[i], u[i], now);
          if (s[i] == 0)
          {
            for (int j = 0; j < n; j++)
            {
              lli now2 = u[i];
              for (int ii = 0; ii < n; ii++)
                if (ii != i)
                  now2 = (t[j] ? now2 | mat[ii][j] : now & mat[ii][j]);
              if (now2 == v[j])
                mat[i][j] = u[i];
            }
          }
        }
      }
      for (int j = 0; j < n; j++)
      {
        lli now = mat[0][j];
        for (int i = 1; i < n; i++)
          now = (t[j] ? now | mat[i][j] : now & mat[i][j]);
        if (now != v[j])
        {
          DEBUG printf("column %d %d %lld %lld\n", j, t[j], v[j], now);
          if (t[j] == 0)
          {
            for (int i = 0; i < n; i++)
            {
              lli now2 = v[j];
              for (int jj = 0; jj < n; jj++)
                if (jj != j)
                  now2 = (s[i] ? now2 | mat[i][jj] : now & mat[i][jj]);
              DEBUG printf("\t\t%d %d %lld %lld\n", j, i, now2, u[i]);
              if (now2 == u[i])
                mat[i][j] = v[j];
            }
          }
        }
      }
    }

    for (int i = 0; i < n; i++)
    {
      lli now = mat[i][0];
      for (int j = 1; j < n; j++)
        now = (s[i] ? now | mat[i][j] : now & mat[i][j]);
      if (now != u[i])
        can = false;
    }

    for (int j = 0; j < n; j++)
    {
      lli now = mat[0][j];
      for (int i = 1; i < n; i++)
        now = (t[j] ? now | mat[i][j] : now & mat[i][j]);
      if (now != v[j])
        can = false;
    }

    if (!can) printf("-1\n");
    else
      for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
          printf("%lld%c", mat[i][j], j < n - 1 ? ' ' : '\n');
  }
  return 0;
}