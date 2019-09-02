#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    lli a, b, n; scanf("%lld %lld %lld", &a, &b, &n);
    printf("%lld\n", n % 3 == 0 ? a : n % 3 == 1 ? b : a ^ b);
  }
  return(0);
}
