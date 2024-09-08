#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int a, b;
  while (~scanf("%d %d", &a, &b))
  {
    printf("%.3Lf\n", (long double) b / a);
  }
  return 0;
}
