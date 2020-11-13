#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
// #define double double
using namespace std;

double u0, b;
double lol = 1000000000;
double f(double x)
{
  return floor(pow((double)2, b - x*x)) / lol;
}

int main()
{
  while (scanf("%lf %lf", &u0, &b) != EOF)
  {
    double x = u0, prv = 0;
    for (int i = 0; i < 1e7; i++)
    {
      prv = x;
      x = f(x);
    }
    printf("%.15lf\n", x + prv);
  }
  return 0;
}