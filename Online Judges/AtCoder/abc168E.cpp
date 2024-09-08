#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const lli mod = 1e9 + 7;

lli modPow(lli x, lli y)
{
  lli ans = 1;
  while (y)
  {
    if (y & 1LL) ans = ans * x % mod;
    x = x * x % mod, y >>= 1LL;
  }
  return ans;
}

int main()
{
  int n;
  while (scanf("%d", &n) != EOF)
  {
    lli a[n], b[n];
    map<pair<lli, lli>, int> cnt, lol;
    for (int i = 0; i < n; i++)
    {
      scanf("%lld %lld", &a[i], &b[i]);
      // if (a[i] > b[i]) swap(a[i], b[i]);
      lli g = gcd(a[i], b[i]);
      a[i] /= g, b[i] /= g;
      pair<lli, lli> u = {a[i], b[i]};
      if (!cnt.count(u)) cnt[u] = 0;
      cnt[u]++;
    }

    lli ans = 0;
    lli invalidsSum = 0;
    for (int i = 0; i < n; i++)
    {
      ans = (ans + modPow(2, n - i - 1)) % mod; // all combinations

      pair<lli, lli> u = {a[i], b[i]};
      lli invalids = 0;
      if (a[i] == 0 && b[i] == 0) invalids = n - i - 1;
      else if (a[i] == 0) invalids = cnt[{0, -b[i]}];
      else if (b[i] == 0) invalids = cnt[{-a[i], 0}];
      else if (a[i] < 0 && b[i] > 0) invalids = cnt[{b[i], -a[i]}] + (-a[i] != b[i])*cnt[{-b[i], a[i]}];
      else invalids = cnt[{b[i], -a[i]}] + (-a[i] != b[i])*cnt[{-b[i], a[i]}];
      lli rem = (n - i) - invalids;
      lli corInvalids = 0, corRem = 0;
      for (int j = i + 1; j < n; j++)
        if (a[i] * a[j] + b[i] * b[j] == 0)
          corInvalids++;
        else
          corRem++;
      if (rem) rem--;
      printf("(%lld, %lld) - %lld (%lld) %lld (%lld)\n", a[i], b[i], invalids, corInvalids, rem, corRem);
      cnt[u]--;
      if (!lol.count(u)) lol[u] = 0;
      if (invalids)
      {
        ans = (ans - modPow(2, n - 2 - invalidsSum) + mod) % mod;
        invalidsSum += max(1, cnt[u]);
      }
      lol[u]++;
    }
    printf("%lld\n", ans);
  }
  return 0;
}