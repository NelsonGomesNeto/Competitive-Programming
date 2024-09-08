#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n, k;

lli kxor(int x, int y)
{
  lli res = 0, p = 1;
  while (x || y)
  {
    lli a = x % k, b = y % k;
    res += p * (((a - b) % k + k) % k);
    p *= k;
    x /= k, y /= k;
  }
  return res;
}

int query(int x)
{
  printf("%d\n", x);
  fflush(stdout);

  int res; scanf("%d", &res);
  return res;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d", &n, &k);
    // lli guess = 1 << 18;
    // query(guess);

    // for (int i = n - 1; i >= 0; i--)
    int prv = 0;
    for (int i = 0; i < n; i++)
    {
      int now = kxor(i, prv);

      if (query(now))
        break;
      prv = i;
    }
  }
  return 0;
}
