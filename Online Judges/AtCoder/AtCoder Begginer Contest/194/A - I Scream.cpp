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
    a = a + b;
    int ans = 0;
    if (a >= 15 && b >= 8)
      ans = 1;
    else if (a >= 10 && b >= 3)
      ans = 2;
    else if (a >= 3)
      ans = 3;
    else
      ans = 4;
    printf("%d\n", ans);
  }
  return 0;
}