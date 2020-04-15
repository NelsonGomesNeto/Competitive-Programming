#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  ldouble l;
  while (scanf("%Lf", &l) != EOF)
  {
    ldouble a = l/3;
    printf("%.15Lf\n", a*a*a);
  }
  return 0;
}