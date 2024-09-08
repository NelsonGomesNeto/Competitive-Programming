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
    bool can = false;
    for (int i = 0; 2020 * i <= n; i++)
      can |= (n - i*2020) % 2021 == 0;
    printf("%s\n", can ? "YES" : "NO");
  }
  return 0;
}
