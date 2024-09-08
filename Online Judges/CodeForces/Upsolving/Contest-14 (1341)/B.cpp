#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n, k;
lli a[maxN];
bool peak[maxN];
int acc[maxN + 1];

int main()
{
  int t; scanf("%d", &t);
  while (t--)
  {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]), peak[i] = false;
    for (int i = 1; i < n - 1; i++)
      if (a[i] > a[i - 1] && a[i] > a[i + 1])
      {
        DEBUG printf("\t%d\n", i + 1);
        peak[i] = true;
      }
    for (int i = 0; i < n; i++)
      acc[i + 1] = acc[i] + peak[i];

    int tt = 0, l = 0;
    for (int i = 0; i + k - 1 < n; i++)
    {
      int peaks = acc[i + k - 1] - acc[i + 1];
      DEBUG printf("\t%d %d\n", i + 1, peaks);
      if (peaks > tt)
        tt = peaks, l = i;
    }
    printf("%d %d\n", tt + 1, l + 1);
  }
  return 0;
}
