#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int x, y;
  while (~scanf("%d %d", &x, &y))
  {
    if (x == y) printf("%d\n", x);
    else printf("%d\n", 3 - (x + y));
  }
  return 0;
}