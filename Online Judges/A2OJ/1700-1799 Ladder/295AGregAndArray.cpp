#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n, m, k;
lli a[maxN], inop[maxN], outop[maxN], inadd[maxN], outadd[maxN], op[maxN][3];

int main()
{
  scanf("%d %d %d", &n, &m, &k);
  for (int i = 0; i < n; i ++)
    scanf("%lld", &a[i]);

  for (int i = 0; i < m; i ++)
  {
    for (int j = 0; j < 3; j ++)
      scanf("%lld", &op[i][j]);
    op[i][0] --, op[i][1] --;
  }

  for (int i = 0; i < k; i ++)
  {
    int lo, hi; scanf("%d %d", &lo, &hi); lo --, hi --;
    inop[lo] ++, outop[hi] ++;
  }

  for (lli i = 0, toadd = 0; i < m; i ++)
  {
    toadd += inop[i];
    inadd[op[i][0]] += op[i][2] * toadd;
    outadd[op[i][1]] += op[i][2] * toadd;
    toadd -= outop[i];
  }

  for (lli i = 0, toadd = 0; i < n; i ++)
  {
    toadd += inadd[i];
    a[i] += toadd;
    toadd -= outadd[i];
  }

  for (int i = 0; i < n; i ++)
    printf("%lld%c", a[i], i < n - 1 ? ' ' : '\n');
  return 0;
}