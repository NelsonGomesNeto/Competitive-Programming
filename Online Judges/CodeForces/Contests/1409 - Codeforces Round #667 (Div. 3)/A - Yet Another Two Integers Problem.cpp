#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int t;
  while (scanf("%d", &t) != EOF)
    for (int i = 0; i < t; i++)
    {
      lli a, b; scanf("%lld %lld", &a, &b);
      lli diff = abs(a - b);
      printf("%lld\n", diff / 10 + (diff % 10 != 0));
    }
  return 0;
}