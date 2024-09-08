#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 20; int n;
lli fat[maxN + 1];

int main()
{
  fat[0] = 1;
  for (int i = 1; i <= maxN; i++)
    fat[i] = fat[i - 1] * i;
  while (scanf("%d", &n) != EOF)
  {
    lli ans = (fat[n] >> 1LL) / (lli)((n >> 1LL) * (n >> 1LL));
    printf("%lld\n", ans);
  }
  return 0;
}
