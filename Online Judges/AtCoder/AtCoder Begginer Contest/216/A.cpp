#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int x, y;
  while (~scanf("%d.%d", &x, &y))
  {
    if (y <= 2) printf("%d-\n", x);
    else if (y <= 6) printf("%d\n", x);
    else printf("%d+\n", x);
  }
  return 0;
}