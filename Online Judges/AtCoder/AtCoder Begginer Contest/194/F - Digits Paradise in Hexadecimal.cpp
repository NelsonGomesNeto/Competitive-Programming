#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxSz = 2e5, maxCnt = 16;
char s[maxSz + 1];
int n[maxSz]; int sz, k;

const lli mod = 1e9 + 7;
lli memo[maxSz][maxCnt + 1][2][2];
lli solve(int mask = 0, int i = 0, bool equal = true, bool started = false)
{
  int cnt = __builtin_popcount(mask);
  if (cnt > k)
    return 0;
  if (i == sz)
  {
    return cnt == k && started;
  }

  lli &ans = memo[i][cnt][equal][started];
  if (ans != -1)
    return ans;
  
  ans = 0;
  for (int d = 0; d <= (equal ? n[i] : 15); d++)
    ans = (ans + solve(d == 0 && !started ? mask : mask | (1 << d), i + 1, equal & (d == n[i]), started | (d > 0))) % mod;
  return ans;
}

int main()
{
  while (~scanf(" %s %d", s, &k))
  {
    sz = strlen(s);
    for (int i = 0; i < sz; i++)
    {
      if (s[i] >= '0' && s[i] <= '9')
        n[i] = s[i] - '0';
      else
        n[i] = s[i] - 'A' + 10;
    }

    DEBUG
    {
      printf("%s\n", s);
      for (int i = 0; i < sz; i++)
        printf("%d ", n[i]);
      printf("\n");
    }

    memset(memo, -1, sizeof(memo));
    lli ans = solve();
    printf("%lld\n", ans);
  }
  return 0;
}