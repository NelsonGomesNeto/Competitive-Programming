#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int a, b, c;
  while (~scanf("%d %d %d", &a, &b, &c))
  {
    printf("%d\n", max({b, c, a - (b + c)}));
  }
  return 0;
}