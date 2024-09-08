#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int n, x, t;
  while (scanf("%d %d %d", &n, &x, &t) != EOF)
  {
    printf("%d\n", t * (n / x + (n % x != 0)));
  }
  return 0;
}