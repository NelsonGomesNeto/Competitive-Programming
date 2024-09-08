#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int n;
  while (scanf("%d", &n) != EOF)
  {
    lli a[n], total = 0;
    for (int i = 0; i < n; i++)
    {
      scanf("%lld", &a[i]);
      total ^= a[i];
    }

    for (int i = 0; i < n; i++)
      printf("%lld%c", total ^ a[i], i < n - 1 ? ' ' : '\n');
  }
  return 0;
}