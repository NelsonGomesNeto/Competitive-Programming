#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 2e5 + 1; int n; lli a, b;
char s[maxN];

int main()
{
  // 14 * 5 + 12 * 2
  int t; scanf("%d", &t);
  while (t --)
  {
    scanf("%d %lld %lld", &n, &a, &b);
    scanf(" %s", s);
    // printf("%s\n", s);
    lli ans = b;
    for (int i = 0, prv = '0'; i < n; i ++)
    {
      if (prv == '1' || s[i] == '1') ans += 2*b;
      else ans += b;
      prv = s[i];
    }
    for (int i = 0, prv = '0'; i < n; i ++)
    {
      if (prv != s[i]) ans += 2*a;
      else ans += a;
      prv = s[i];
    }
    for (int i = 0; i < n; i ++)
      if (s[i] == '1')
      {
        while (i + 1 < n && s[i + 1] == '1') i ++;
        int j = i + 1;
        while (j < n && s[j] != '1') j ++;
        if (j < n)
        {
          // printf("%d %d\n", i, j);
          lli down = 4LL*a + (lli)(j - i + 1 - 3)*(a + b);
          lli up = 2LL*a + (lli)(j - i + 1 - 3)*(a + 2LL*b);
          if (up < down) ans -= down - up;
        }
      }
    printf("%lld\n", ans);
  }
  return(0);
}
