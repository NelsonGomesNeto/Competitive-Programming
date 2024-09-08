#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n, k;
const lli mod = 1e9 + 7;
char s[maxN + 1];
int n2;

// 0 equal, 1 greater, 2 smaller
lli memo[maxN][2][3];
lli solve(int i = 0, bool equal = true, int rev = 0)
{
  if (i == n2) return equal ? rev == 2 : true;
  lli &ans = memo[i][equal][rev];
  if (ans != -1) return ans;

  ans = 0;
  for (int c = 'a', cc = 0; cc < k; cc++, c++)
  {
    if (!equal || c <= s[i])
    {
      ans = (ans + solve(i + 1, equal & (c == s[i]),
                         c == s[n - i - 1] ? rev : c < s[n - i - 1] ? 2 : 1)) % mod;
    }
  }

  return ans;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d", &n, &k);
    scanf(" %s", s);
    n2 = (n + 1) >> 1;

    memset(memo, -1, sizeof(memo));
    lli ans = solve();
    printf("Case #%d: %lld\n", tt, ans);
  }
  return 0;
}