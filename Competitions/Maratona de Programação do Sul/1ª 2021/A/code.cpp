#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  ldouble a, b;
  while (~scanf("%Lf %Lf", &a, &b))
  {
    ldouble ans = (100 + a) / 100 * (100 + b) - 100;
    printf("%.6Lf\n", ans);
  }
  return 0;
}