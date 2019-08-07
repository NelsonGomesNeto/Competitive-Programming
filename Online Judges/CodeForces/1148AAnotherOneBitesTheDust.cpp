#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
  lli a, b, c; scanf("%lld %lld %lld", &a, &b, &c);
  printf("%lld\n", min(a + b, 2*min(a, b) + 1) + c*2);

  return(0);
}
