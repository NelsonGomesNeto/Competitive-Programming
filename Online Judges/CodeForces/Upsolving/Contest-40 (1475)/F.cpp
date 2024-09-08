#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
  source(0) -[1]> rows (1 : n) -[]
*/

const int maxN = 1e3; int n;
int a[maxN][maxN], b[maxN][maxN];
int aux[maxN][maxN];

void fliph(int i)
{
  for (int j = 0; j < n; j++)
    a[i][j] = !a[i][j];
}
void flipv(int j)
{
  for (int i = 0; i < n; i++)
    a[i][j] = !a[i][j];
}
bool check()
{
  bool valid = true;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      valid &= a[i][j] == b[i][j];
  return valid;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        scanf("%1d", &a[i][j]);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        aux[i][j] = a[i][j];

    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        scanf("%1d", &b[i][j]);

    bool can = true;
    int ii, jj;
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        if (a[i][j] != b[i][j])
          can = false, ii = i, jj = j;

    if (!can)
    {
      // horizontal flip
      fliph(ii);
      for (int i = 0; i < n; i++)
        if (a[i][jj] != b[i][jj])
          fliph(i);
      for (int j = 0; j < n; j++)
        if (a[ii][j] != b[ii][j])
          flipv(j);
      // for (int i = 0; i < n; i++)
      // {
      //   printf("\t");
      //   for (int j = 0; j < n; j++)
      //     printf("%d%c", a[i][j], j < n - 1 ? ' ' : '\n');
      // }
      can |= check();

      // vertical flip
      for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
          a[i][j] = aux[i][j];
      flipv(jj);
      for (int i = 0; i < n; i++)
        if (a[i][jj] != b[i][jj])
          fliph(i);
      for (int j = 0; j < n; j++)
        if (a[ii][j] != b[ii][j])
          flipv(j);
      can |= check();
    }

    printf("%s\n", can ? "YES" : "NO");
  }
  return 0;
}
