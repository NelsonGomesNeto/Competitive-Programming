#include <bits/stdc++.h>
#define lli long long int
using namespace std;
int mat[100][100], n, m;

lli evaluate(int k)
{
  lli now = 0;
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < m; j ++)
      now += abs(mat[i][j] - k);
  return(now);
}

lli evaluateRange(int lo, int hi)
{
  lli best = 999999999;
  for (int k = lo; k <= hi; k ++)
    best = min(best, evaluate(k));
  return(best);
}

lli ternarySearch(int lo, int hi)
{
  if (lo >= hi - 3) return(evaluateRange(lo, hi));
  int mlo = (2*lo + hi) / 3, mhi = (lo + 2*hi) / 3 + 1;
  lli elo = evaluate(mlo), ehi = evaluate(mhi);
  if (elo < ehi)
    return(ternarySearch(lo, mhi));
  else
    return(ternarySearch(mlo, hi));
}

int main()
{
  int d; scanf("%d %d %d", &n, &m, &d);
  int can = 1, rest = -1;
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < m; j ++)
    {
      scanf("%d", &mat[i][j]);
      if (rest == -1) rest = mat[i][j] % d;
      if (mat[i][j] % d != rest) can = 0;
      mat[i][j] = (mat[i][j] / d) + rest;
    }

  if (!can) printf("-1\n");
  else
  {
    int minimum = 999999, maximum = -1;
    lli mean = 0;
    for (int i = 0; i < n; i ++)
      for (int j = 0; j < m; j ++)
      {
        minimum = min(minimum, mat[i][j]);
        maximum = max(maximum, mat[i][j]);
        mean += mat[i][j];
      }

    lli best = ternarySearch(minimum, maximum);

    printf("%lld\n", best);
  }

  return(0);
}
