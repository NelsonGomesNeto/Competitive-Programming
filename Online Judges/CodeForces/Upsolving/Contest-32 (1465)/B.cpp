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
    lli n; scanf("%lld", &n);

    while (true)
    {
      vector<int> divisors;
      lli aux = n;
      while (aux)
      {
        int d = aux % 10;
        if (d != 0)
          divisors.push_back(d);
        aux /= 10;
      }

      lli toAdd = 0;
      for (int d: divisors)
        if (n % d)
          toAdd = 1;
      
      if (toAdd == 0)
        break;

      n += toAdd;
    }

    printf("%lld\n", n);
  }
  return 0;
}
