#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

lli getPot(lli num)
{
  lli pot = 1;
  while (num)
    num /= 10, pot *= 10;
  return pot;
}

int main()
{
  lli n;
  while (~scanf("%lld", &n))
  {
    lli half = sqrt(n);
    lli ans = 0;
    for (lli i = 1; i <= half; i++)
    {
      lli pot = getPot(i);
      if (i + i*pot <= n)
        ans++;
    }
    printf("%lld\n", ans);
  }
  return 0;
}