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
    lli n, m, x; scanf("%lld %lld %lld", &n, &m, &x);
    lli i = (x - 1) / n, j = (x - 1) % n;
    lli number = j * m + i + 1;
    printf("%lld\n", number);
  }
  return 0;
}
