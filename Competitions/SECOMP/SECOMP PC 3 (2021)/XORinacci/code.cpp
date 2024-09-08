#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int a, b, n;
  while (~scanf("%d %d %d", &a, &b, &n))
  {
    int ans = n % 3 == 0 ? a : n % 3 == 1 ? b : a ^ b;
    printf("%d\n", ans);
  }
  return 0;
}