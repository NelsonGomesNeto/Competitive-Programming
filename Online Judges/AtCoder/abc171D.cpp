#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
int cnt[maxN + 1];
lli ans;

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    memset(cnt, 0, sizeof(cnt)), ans = 0;
    for (int i = 0; i < n; i++)
    {
      int a; scanf("%d", &a);
      cnt[a]++, ans += a;
    }
    DEBUG printf("\t%lld\n", ans);

    int q; scanf("%d", &q);
    while (q--)
    {
      int b, c; scanf("%d %d", &b, &c);
      ans -= (lli)cnt[b]*b, ans += (lli)cnt[b]*c;
      cnt[c] += cnt[b];
      cnt[b] = 0;
      printf("%lld\n", ans);
    }
  }
  return 0;
}