#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 301;
const lli inf = 1e18;
char s[maxN]; int n; lli k;

lli solve()
{
  lli ans = 0;
  for (int i = 0; i < n - 1; i ++)
    if (s[i] == s[i + 1])
      ans ++, i ++;
  return ans;
}

int main()
{
  scanf("%s %lld", s, &k);
  n = strlen(s); int originalSize = n;

  lli f[4]; f[0] = 0; f[1] = solve();
  for (int j = 1; j < 3; j ++)
  {
    for (int i = 0; i < originalSize; i ++)
      s[i + originalSize*j] = s[i];
    n += originalSize;
    f[j + 1] = solve();
  }

  if (k <= 3) printf("%lld\n", f[k]);
  else
  {
    lli ans = f[1];
    // ans += (k - 1) * (f[2] - f[1]);
    ans += ((k - 1) >> 1LL) * (f[3] - f[1]);
    if ((k - 1) & 1LL) ans += f[2] - f[1];
    printf("%lld\n", ans);
  }

  return 0;
}