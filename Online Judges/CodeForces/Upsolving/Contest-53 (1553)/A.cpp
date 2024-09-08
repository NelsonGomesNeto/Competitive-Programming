#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int s(int x)
{
  int ans = 0;
  while (x)
  {
    ans += x % 10;
    x /= 10;
  }
  return ans;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    lli n; scanf("%lld", &n);
    printf("%lld\n", n / 10 + (n % 10 == 9));
  }
  return 0;
}
