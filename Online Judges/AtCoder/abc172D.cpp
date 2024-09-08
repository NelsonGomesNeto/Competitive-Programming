#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e7;
int divisors[maxN + 1];

int main()
{
  for (int i = 1; i <= maxN; i ++)
    for (int j = i; (lli)i*j <= maxN; j++)
      divisors[i*j] += 1 + (i != j);

  int n;
  while (scanf("%d", &n) != EOF)
  {
    lli ans = 0;
    for (int i = 1; i <= n; i++)
      ans += (lli)i * divisors[i];
    printf("%lld\n", ans);
  }

  return 0;
}