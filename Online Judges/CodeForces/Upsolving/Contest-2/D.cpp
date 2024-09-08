#include <bits/stdc++.h>
#define DEBUG if(1)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 4e5; int n;
lli a[maxN];

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i ++)
      scanf("%lld", &a[i]);
    lli ans = 0;
    for (int i = 0; i < n; i ++)
      for (int j = i + 1; j < n; j ++)
        ans ^= a[i] + a[j];
    printf("%lld\n", ans);
  }
  return 0;
}
