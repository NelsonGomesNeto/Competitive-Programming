#include <bits/stdc++.h>
#define DEBUG if(1)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5, maxP = 1e4 + 1; int n, p;
char s[maxN + 1];
lli cnt[maxP]; int acc[maxN + 1];

/* Tutorial:
  Notice that every prime, except 2 and 5, are coprimes with 10 (gcd(p, 10) == 1).
  The case where p == 2 or 5 is much easier:
    ans = 0
    for each digit d:
      if (d % p == 0)
        ans += digitsPos + 1
  Now back to every other prime:
    We can represent every number as: digit[0] * 10^0 + digit[1] * 10^1 + ...
    Also, if 10 * a % p == 0: a % p == 0 is also true (since gcd(p, 10) == 1)

    Using accumulated sum, we can build acc from right to left such that:
      acc[i] = (digit[n - 1]*10^0 + digit[n - 2]*10^1 + ... + digit[i]*10^(n - 1 - i)) % p
    With that, we can build any number:
      int(s[i : j]) % p = (acc[i] - acc[j + 1]) / 10^(n - 1 - j) % p
        * iff int(s[i : j]) % p == 0
      BUT, we actually don't need to divide by 10^(n - 1 - j), since gcd(p, 10) == 1

    So, we just need to count how many remainder happend and:
    ans = cnt[i] * (cnt[i] - 1) / 2 (for i in [0 : p - 1])
    The idea here is that we are counting every (i, j) combination where i <= j.
    (Since acc[i] - acc[j] == 0 iff acc[i] == acc[j] tehe)
*/

int main()
{
  while (scanf("%d %d", &n, &p) != EOF)
  {
    memset(cnt, 0, sizeof(cnt));

    scanf(" %s", s);

    if (p == 2 || p == 5)
    {
      lli ans = 0;
      for (int i = 0; i < n; i++)
        if ((s[i] - '0') % p == 0)
          ans += i + 1;
      printf("%lld\n", ans);
      continue;
    }

    acc[n] = 0;
    for (int i = n - 1, pot = 1; i >= 0; i--, pot = (pot * 10) % p)
      acc[i] = (acc[i + 1] + (s[i] - '0') * pot) % p;

    DEBUG
      for (int i = 0; i <= n; i++)
        printf("%d%c", acc[i], i < n ? ' ' : '\n');

    cnt[0] = 1;
    for (int i = 0; i < n; i++)
      cnt[acc[i]]++;

    lli ans = 0;
    for (int i = 0; i < p; i++)
      ans += cnt[i] * (cnt[i] - 1) >> 1LL;

    printf("%lld\n", ans);
  }
  return 0;
}
