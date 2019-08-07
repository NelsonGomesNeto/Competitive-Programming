#include <bits/stdc++.h>
#define lli long long int
using namespace std;

bool notPrime(lli n)
{
  for (int i = 2, end = sqrt(n); i <= end; i ++)
    if (n % i == 0)
      return(true);
  return(false);
}

int main()
{
  lli n; scanf("%lld", &n);
  while (notPrime(n)) n --;
  printf("%lld\n", n);
  return(0);
}