#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  lli sum = 0;
  lli mass;
  while (scanf("%lld", &mass) != EOF)
  {
    while (mass)
    {
      mass = mass / 3LL - 2LL;
      if (mass < 0) mass = 0;
      sum += mass;
    }
  }
  
  printf("%lld\n", sum);
  return 0;
}