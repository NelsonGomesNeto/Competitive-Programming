#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  lli a, b, c;
  while (~scanf("%lld %lld %lld", &a, &b, &c))
  {
    char ans = '=';
    if (a == b)
      ;
    else if (a < 0 && b < 0)
    {
      if (!(c & 1)) ans = a < b ? '<' : '>';
      else ans = a > b ? '<' : '>';
    }
    else if (a >= 0 && b >= 0)
    {
      ans = a > b ? '>' : '<';
    }
    else if (a <= 0 && b >= 0)
    {
      if (!(c & 1)) ans = -a < b ? '<' : (-a == b ? '=' : '>');
      else ans = '<';
    }
    else if (a >= 0 && b <= 0)
    {
      if (!(c & 1)) ans = a < -b ? '<' : (a == -b ? '=' : '>');
      else ans = '>';
    }

    printf("%c\n", ans);
  }
  return 0;
}