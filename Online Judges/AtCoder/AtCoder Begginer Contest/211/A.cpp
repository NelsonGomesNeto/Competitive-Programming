#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  double a, b; scanf("%lf %lf", &a, &b);
  double c = (a - b) / 3 + b;
  printf("%.15lf\n", c);
  return 0;
}