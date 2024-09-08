#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int v, t, s, d;
  while (~scanf("%d %d %d %d", &v, &t, &s, &d))
  {
    printf("%s\n", !(v * t <= d && d <= v * s) ? "Yes" : "No");
  }
  return 0;
}