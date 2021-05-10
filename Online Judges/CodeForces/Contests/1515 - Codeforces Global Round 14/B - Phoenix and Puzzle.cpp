#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

map<lli, bool> memo;

int main()
{
  memo.clear();

  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    /*
      2 4 8 16 18 32
    */
    lli n; scanf("%lld", &n);

    bool can = false;

    if (n <= 4) can = n == 2 || n == 4;
    else
    {
      lli aux1 = n >> 1, aux2 = n >> 2;
      lli sq1 = sqrt(aux1), sq2 = sqrt(aux2);
      can = (sq1*sq1 == aux1 && n % 2 == 0) || (sq2*sq2 == aux2 && n % 4 == 0);
    }

    printf("%s\n", can ? "YES" : "NO");
  }
  return 0;
}
