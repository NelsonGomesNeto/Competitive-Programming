#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    lli a, b, n, s; scanf("%lld %lld %lld %lld", &a, &b, &n, &s);
    lli x = s / n;
    if (x <= a && s - x * n <= b) printf("YES\n");
    else if (s - min(x, a) * n <= b) printf("YES\n");
    else printf("NO\n");
  }
  return 0;
}
