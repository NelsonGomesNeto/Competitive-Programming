// #include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double
// using namespace std;

const int maxN = 1e4, maxM = 1e2;
int n, m;

int compare(const void *a, const void *b)
{
  return (*(int *)a - *(int *)b);
}

int main()
{
  while (~scanf("%d %d", &n, &m))
  {
    int a[n][m];

    for (int i = 0; i < n; ++i)
    {
      for (int j = 0; j < m; ++j)
        scanf("%d", &a[i][j]);
      qsort(a[i], m, sizeof(int), compare);
    }

    lli ans = 0;
    for (int l = 0; l < n; ++l)
      for (int r = l + 1; r < n; ++r)
        for (int i = 0, j = 0; i < m;)
        {
          if (j == m || a[l][i] < a[r][j])
          {
            ans += 1 + i + j;
            ++i;
          }
          else
            ++j;
        }
    printf("%lld\n", ans);
  }
  return 0;
}
