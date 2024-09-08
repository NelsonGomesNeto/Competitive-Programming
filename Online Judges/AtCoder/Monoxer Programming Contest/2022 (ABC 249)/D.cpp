#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
a[i] / a[j] = a[k]
a[i] = a[k] * a[j]

for i in range(n):
  for d in divisors(a[i]):
    ans += count(d) * count(a[i] / d)
*/

const int maxN = 2e5; int n;
int a[maxN];
int cnt[maxN + 1];

vector<int> divisors[maxN + 1];

int main()
{
  for (int i = 1; i <= maxN; ++i)
    for (int d = 1, end = sqrt(i); d <= end; ++d)
      if (i % d == 0)
      {
        divisors[i].push_back(d);
        int dd = i / d;
        if (d != dd && i % dd == 0)
          divisors[i].push_back(dd);
      }

  while (~scanf("%d", &n))
  {
    fill(cnt, cnt+maxN+1, 0);
    for (int i = 0; i < n; ++i)
    {
      scanf("%d", &a[i]);
      ++cnt[a[i]];
    }

    lli ans = 0;
    for (int i = 0; i < n; ++i)
      for (int d : divisors[a[i]])
      {
        DEBUG printf("\t%d - %d\n", a[i], d);
        ans += (lli)cnt[d] * cnt[a[i] / d];
      }
    printf("%lld\n", ans);
  }
  return 0;
}
