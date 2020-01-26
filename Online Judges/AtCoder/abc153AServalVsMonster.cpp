#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  lli h, a;
  while (scanf("%lld %lld", &h, &a) != EOF)
    printf("%lld\n", h / a + (h % a != 0));
  return 0;
}