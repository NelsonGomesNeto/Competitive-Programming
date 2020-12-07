#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 2e5;
char s[maxN + 1];
int sum[maxN + 1];
list<int> leftZero[maxN + 1];
int digits(int num)
{
  int sz = 0;
  while (num) num >>= 1, sz ++;
  return sz;
}
int ones(int num)
{
  int o = 0;
  while (num)
  {
    o += num & 1;
    num >>= 1;
  }
  return o;
}

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    memset(s, '\0', sizeof(s));
    scanf(" %s", s); int n = strlen(s);
    for (int i = 0; i < n; i ++) leftZero[i].clear();

    for (int i = 0; i < n; i ++)
      sum[i + 1] = sum[i] + (s[i] == '0');

    int zeroAcc = 0;
    for (int i = n - 1; i >= 0; i --)
    {
      if (s[i] == '1') zeroAcc = 0;
      else zeroAcc ++;
      leftZero[zeroAcc].push_back(i);
    }

    lli ans = 0;
    for (int bitmask = 1; bitmask <= n; bitmask ++)
    {
      int sz = bitmask, dsz = digits(bitmask), one = ones(bitmask);
      int zero = sz - one, lzero = sz - dsz;
      if (one <= n - sum[n] && zero <= sum[n])
        for (int j: leftZero[lzero])
          if (sum[j + sz] - sum[j] == zero)
          {
            bool valid = true;
            for (int k = 0, kk = dsz - 1; k < dsz && valid; k ++, kk --)
              if ((s[j + k + lzero] - '0') != ((bitmask >> kk) & 1))
                valid = false;
            ans += valid;
          }
    }
    printf("%lld\n", ans);
  }
  return(0);
}
