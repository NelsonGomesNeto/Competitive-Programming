#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const lli mod = 998244353;

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

int q;

int main()
{
  while (~scanf("%d", &q))
  {
    deque<int> digits;
    digits.push_back(1);
    lli ans = 1;
    while (q--)
    {
      int op;
      scanf("%d", &op);
      if (op == 1)
      {
        int x;
        scanf("%d", &x);
        ans = (ans * 10 % mod + x) % mod;
        digits.push_back(x);
      }
      else if (op == 2)
      {
        int d = digits.front();
        ans = (ans - d * modPow(10, digits.size() - 1) % mod + mod) % mod;
        digits.pop_front();
      }
      else
      {
        printf("%lld\n", ans);
      }
    }
  }
  return 0;
}
