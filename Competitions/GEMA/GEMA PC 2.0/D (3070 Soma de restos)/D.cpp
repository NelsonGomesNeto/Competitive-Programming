#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e3; int n, m;
int a[maxN];
int acc[maxN][maxN + 1];

int main()
{
  while (scanf("%d %d", &n, &m) != EOF)
  {
    for (int i = 0; i < n; i ++)
      scanf("%d", &a[i]);

    for (int i = 0; i < m; i ++)
      for (int j = 0; j < n; j ++)
        acc[i][j + 1] = acc[i][j] + (a[j] % m == i);

    int q; scanf("%d", &q);
    while (q --)
    {
      int l, r, mm; scanf("%d %d %d", &l, &r, &mm); l --, r --;
      printf("%d\n", acc[mm][r + 1] - acc[mm][l]);
    }
  }
  return 0;
}