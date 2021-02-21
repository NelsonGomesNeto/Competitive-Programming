#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int k;
  while (~scanf("%d", &k))
  {
    lli ans = 0;
    for (lli a = 1; a <= k; a++)
      for (lli b = 1; a*b <= k; b++)
        for (lli c = 1, hehe = a*b; hehe*c <= k; c++)
          ans++;
    printf("%lld\n", ans);
  }
  return 0;
}