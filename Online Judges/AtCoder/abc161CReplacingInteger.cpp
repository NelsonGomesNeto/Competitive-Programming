#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  lli n, k;
  while (scanf("%lld %lld", &n, &k) != EOF)
    printf("%lld\n", min(n % k, abs(n % k - k)));
  return 0;
}