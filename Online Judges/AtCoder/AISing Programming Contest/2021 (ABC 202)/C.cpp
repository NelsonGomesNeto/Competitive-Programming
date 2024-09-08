#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
int a[maxN], b[maxN], c[maxN];
int cnta[maxN + 1], cntb[maxN + 1];

int main()
{
  while (~scanf("%d", &n))
  {
    memset(cnta, 0, sizeof(cnta)), memset(cntb, 0, sizeof(cntb));
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &a[i]);
      cnta[a[i]]++;
    }
    for (int i = 0; i < n; i++)
      scanf("%d", &b[i]);
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &c[i]);
      c[i]--;
      cntb[b[c[i]]]++;
    }

    lli ans = 0;
    for (int i = 0; i <= n; i++)
      ans += (lli)cnta[i] * cntb[i];
    printf("%lld\n", ans);
  }
  return 0;
}