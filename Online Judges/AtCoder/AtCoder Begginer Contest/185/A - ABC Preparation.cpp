#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int a, b, c, d;
  while (~scanf("%d %d %d %d", &a, &b, &c, &d))
    printf("%d\n", min({a, b, c, d}));
  return 0;
}