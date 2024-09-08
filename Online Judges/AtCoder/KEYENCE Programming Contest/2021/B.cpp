#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e5; int n, k;
int a[maxN];
int cnt[maxN];
int base[maxN];

int main()
{
  while (~scanf("%d %d", &n, &k))
  {
    for (int i = 0; i < n; i++)
      scanf("%d", &a[i]);

    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < n; i++)
      cnt[a[i]]++;

    lli ans = 0;
    int base = k;
    for (int i = 0; i < n; i++)
    {
      base = min(base, cnt[i]);
      ans += base;
    }
    printf("%lld\n", ans);
  }
  return 0;
}