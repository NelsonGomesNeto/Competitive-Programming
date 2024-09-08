#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  double a, b;
  while (~scanf("%lf %lf", &a, &b))
  {
    double ans = b * a / 100;
    printf("%lf\n", ans);
  }
  return 0;
}