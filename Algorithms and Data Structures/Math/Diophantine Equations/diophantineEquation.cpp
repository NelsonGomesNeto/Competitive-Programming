#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
  Solves equations of the form:
    a*x + b*y = c

  Every other solution can be found through:
  {
    x = x0 + k * (b / g)
    y = y0 - k * (a / g)
  }

  Be *VERY* careful with overflow
  (You can almost always use __int128 as well)
*/

lli gcd(lli a, lli b, lli& x, lli& y)
{
  if (b == 0)
  {
    x = 1, y = 0;
    return a;
  }

  lli x1, y1;
  lli d = gcd(b, a % b, x1, y1);
  x = y1;
  y = x1 - y1 * (a / b);
  return d;
}

bool findAnySolution(lli a, lli b, lli c, lli &x0, lli &y0, lli &g)
{
  g = gcd(abs(a), abs(b), x0, y0);
  if (c % g)
    return false;

  x0 *= c / g;
  y0 *= c / g;
  if (a < 0) x0 = -x0;
  if (b < 0) y0 = -y0;
  return true;
}

int main()
{
  
  return 0;
}