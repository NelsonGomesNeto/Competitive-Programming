#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    int a, b, c, m; scanf("%d %d %d %d", &a, &b, &c, &m);
    int minimum = max({a, b, c}) - (a + b + c) - max({a, b, c}), maximum = max(0, a - 1) + max(0, b - 1) + max(0, c - 1);
    if (m < minimum || m > maximum) printf("NO\n");
    else printf("YES\n");
  }
  return 0;
}
