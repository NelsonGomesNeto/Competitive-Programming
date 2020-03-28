#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5, maxP = 1e3 + 1; int n, k;
int p[maxN];
ldouble acc[maxN + 1];

int main()
{
  ldouble expected[maxP];
  for (int i = 1; i < maxP; i ++)
  {
    expected[i] = 0;
    for (int j = 1; j <= i; j ++)
      expected[i] += j;
    expected[i] /= i;
  }

  while (scanf("%d %d", &n, &k) != EOF)
  {
    for (int i = 0; i < n; i ++)
      scanf("%d", &p[i]);

    for (int i = 0; i < n; i ++)
      acc[i + 1] = acc[i] + expected[p[i]];

    ldouble ans = 0;
    for (int i = 0; i + k - 1 < n; i ++)
      ans = max(ans, acc[i + k] - acc[i]);
    printf("%.15Lf\n", ans);
  }
  return 0;
}