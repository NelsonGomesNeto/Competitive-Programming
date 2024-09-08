#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int x, y, z;
  while (~scanf("%d %d %d", &x, &y, &z))
  {
    // y / x > w / z
    // z*y > w*x
    // z*y / x > w
    int w = z * y / x - (z * y % x == 0);
    printf("%d\n", w);

  }
  return 0;
}