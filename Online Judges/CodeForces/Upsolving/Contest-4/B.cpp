#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
lli a[maxN], b[maxN];

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i++)
      scanf("%lld", &b[i]);

    lli x = a[0] = b[0];
    for (int i = 1; i < n; i++)
    {
      a[i] = b[i] + x;
      x = max(x, a[i]);
    }

    for (int i = 0; i < n; i++)
      printf("%lld%c", a[i], i < n - 1 ? ' ' : '\n');
  }
  return 0;
}
/*
b[i] = a[i] - x[i]
b[i] + x[i] = a[i]
*/