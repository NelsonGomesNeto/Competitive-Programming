#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

void fastReadInt(int &x)
{
  bool neg = false;
  int c = ' ';
  x = 0;
  while (c != '-' && (c < '0' || c > '9'))
    c = getchar();
 
  if (c == '-')
    neg = true, c = getchar();
 
  for ( ; (c > 47 && c < 58); c = getchar())
    x = (x<<1) + (x<<3) + c - 48;
  if (neg)
    x *=-1;
}

int main()
{
  
  return 0;
}
