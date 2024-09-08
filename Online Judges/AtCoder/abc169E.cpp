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
    lli a[n], b[n];
    for (int i = 0; i < n; i++)
      scanf("%lld %lld", &a[i], &b[i]);

    sort(a, a+n), sort(b, b+n);

    if (n & 1) printf("%lld\n", b[n >> 1] - a[n >> 1] + 1);
    else printf("%lld\n", (b[n >> 1] + b[(n - 1) >> 1]) - (a[n >> 1] + a[(n - 1) >> 1]) + 1);
  }
  return 0;
}