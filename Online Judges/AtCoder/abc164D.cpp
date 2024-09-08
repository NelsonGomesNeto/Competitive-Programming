#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
const int mod = 2019;
char s[maxN + 1];
int acc[maxN + 1], cnt[mod + 1];

int main()
{
  while (scanf(" %s", s) != EOF)
  {
    memset(cnt, 0, sizeof(cnt));
    n = strlen(s);
    acc[n] = 0;
    for (int i = n - 1, p = 1; i >= 0; i--, p = (p * 10) % mod)
      acc[i] = (acc[i + 1] + p*(s[i] - '0')) % mod;

    cnt[0] = 1;
    for (int i = 0; i < n; i++)
      cnt[acc[i]]++;

    lli ans = 0;
    for (int i = 0; i < mod; i++)
    {
      DEBUG
        if (cnt[i])
          printf("\t%d %d\n", i, cnt[i]);
      ans += ((lli)cnt[i]*(cnt[i] - 1)) >> 1LL;
    }
    printf("%lld\n", ans);
  }
  return 0;
}