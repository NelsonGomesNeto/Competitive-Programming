#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 40000; int n, m, k;
int a[maxN], b[maxN];
int aCnt[maxN + 2], bCnt[maxN + 2];

int main()
{
  while (scanf("%d %d %d", &n, &m, &k) != EOF)
  {
    memset(aCnt, 0, sizeof(aCnt)), memset(bCnt, 0, sizeof(bCnt));

    for (int i = 0; i < n; i ++)
      scanf("%d", &a[i]);
    for (int i = 0; i < m; i ++)
      scanf("%d", &b[i]);

    for (int i = 0; i < n; i ++)
    {
      if (a[i] != 1) continue;
      int j = i;
      while (j + 1 < n && a[j + 1] == 1) j ++;
      DEBUG printf("\ta %d\n", j - i + 1);
      for (int kk = j - i + 1, sz = j - i + 1; kk >= 1; kk --)
        aCnt[kk] += sz - kk + 1;
      i = j;
    }
    for (int i = 0; i < m; i ++)
    {
      if (b[i] != 1) continue;
      int j = i;
      while (j + 1 < m && b[j + 1] == 1) j ++;
      DEBUG printf("\tb %d\n", j - i + 1);
      for (int kk = j - i + 1, sz = j - i + 1; kk >= 1; kk --)
        bCnt[kk] += sz - kk + 1;
      i = j;
    }

    lli ans = 0;
    set<int> divisors;
    for (int nn = 1, end = sqrt(k); nn <= end; nn ++)
    {
      if (k % nn == 0)
        divisors.insert(nn);
      if (k % (k / nn) == 0)
        divisors.insert(k / nn);
    }
    for (int nn: divisors)
    {
      int mm = k / nn;
      if (nn > n || mm > m) continue;
      DEBUG printf("%d (%d) %d (%d)\n", nn, aCnt[nn], mm, bCnt[mm]);
      ans += aCnt[nn] * bCnt[mm];
    }
    printf("%lld\n", ans);
  }
  return 0;
}
