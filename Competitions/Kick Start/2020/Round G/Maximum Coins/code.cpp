#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3; int n;
lli c[maxN][maxN];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        scanf("%lld", &c[i][j]);

    lli ans = 0;
    for (int i = 0; i < n; i++)
    {
      lli sum = 0;
      for (int ii = i, j = 0; ii < n && j < n; ii++, j++)
        sum += c[ii][j];
      ans = max(ans, sum);
    }

    for (int j = 0; j < n; j++)
    {
      lli sum = 0;
      for (int i = 0, jj = j; i < n && jj < n; i++, jj++)
        sum += c[i][jj];
      ans = max(ans, sum);
    }

    printf("Case #%d: %lli\n", tt, ans);
  }
  return 0;
}