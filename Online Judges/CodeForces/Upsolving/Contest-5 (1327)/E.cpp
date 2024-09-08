#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5 + 1; int n;
const lli mod = 998244353;
lli cnt[maxN];
void cntBlocks(int number)
{
  vector<int> digits;
  for (int i = 0; i < n; i++)
  {
    digits.push_back(number % 10);
    number /= 10;
  }
  for (int i = 0; i < n; i++)
  {
    int j = i;
    while (j + 1 < n && digits[j + 1] == digits[i]) j++;
    cnt[j - i + 1]++;
    i = j;
  }
  // printf("\t");
  // for (int i = 0; i < n; i++)
  //   printf("%d", digits[i]);
  // printf("\n");
}

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
lli calc(lli k)
{
  if (k == n) return 10;
  if (k == n - 1) return 180;
  lli ans = 10 * 2 * (9 * modPow(10, n - k - 1) % mod) % mod;
  ans = (ans + 10 * (n - k - 1) * (81 * modPow(10, n - k - 2) % mod)) % mod;
  return ans;
}

int main()
{
  DEBUG {
    for (n = 1; n <= 5; n++)
    {
      memset(cnt, 0, sizeof(cnt));
      for (int i = 0, end = pow(10, n) - 1; i <= end; i++)
        cntBlocks(i);
      for (int j = 1; j <= n; j++)
        printf("%lld%c", cnt[j], j < n ? ' ' : '\n');
    }
  }

  while (scanf("%d", &n) != EOF)
  {
    for (int i = 1; i <= n; i++)
      printf("%lld%c", calc(i), i < n ? ' ' : '\n');
  }
  return 0;
}
