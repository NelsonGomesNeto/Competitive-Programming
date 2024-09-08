#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int t; scanf("%d", &t);

  for (int tt = 1; tt <= t; tt++)
  {
    lli a, b, c;
    scanf("%lld %lld %lld", &a, &b, &c);

    lli ab = a ^ b;
    lli andAns = 1, orAns = 1;
    for (int i = 0; i <= 60; i++)
    {
      int abi = (ab >> i) & 1;
      int ci = (c >> i) & 1;
      if (abi == 0 && ci == 0)
        andAns *= 2;
      else if (abi == 0 && ci == 1)
        orAns = 0;
      else if (abi == 1 && ci == 0)
        andAns = 0;
      else // abi == 1 && ci == 1
        orAns *= 2;
    }

    printf("%lld %lld\n", andAns, orAns);
  }
  return 0;
}