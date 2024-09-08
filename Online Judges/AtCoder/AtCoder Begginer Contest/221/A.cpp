#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int a, b; scanf("%d %d", &a, &b);
  int hehe = a - b;
  lli ans = 1;
  while (hehe > 0) ans *= 32, hehe--;
  printf("%lld\n", ans);
  return 0;
}