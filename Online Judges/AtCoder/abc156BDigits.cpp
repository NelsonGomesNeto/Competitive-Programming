#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int digits(lli n, int k)
{
  int d = n == 0;
  while (n)
  {
    d ++;
    n /= k;
  }
  return d;
}

int main()
{
  lli n; int k;
  while (scanf("%lld %d", &n, &k) != EOF)
  {
    printf("%d\n", digits(n, k));
  }
  return 0;
}