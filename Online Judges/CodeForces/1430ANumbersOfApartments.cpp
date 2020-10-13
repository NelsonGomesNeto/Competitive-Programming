#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3; int n;

int main()
{
  int t;
  while (scanf("%d", &t) != EOF)
    for (int tt = 1; tt <= t; tt++)
    {
      scanf("%d", &n);
      bool done = false;
      int sevens = n / 7, fives, threes;
      for (sevens; sevens >= 0; sevens--)
      {
        fives = (n - sevens * 7) / 5;
        for (fives; fives >= 0; fives--)
        {
          threes = (n - sevens * 7 - fives * 5) / 3;
          if (n == sevens * 7 + fives * 5 + threes * 3)
          {
            done = true;
            break;
          }
        }
        if (done) break;
      }
      if (!done) printf("-1\n");
      else printf("%d %d %d\n", threes, fives, sevens);
    }
  return 0;
}
