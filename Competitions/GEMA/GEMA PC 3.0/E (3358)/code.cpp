#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int t;
  while (scanf("%d", &t) != EOF)
    for (int tt = 1; tt <= t; tt++)
    {
      int n; scanf("%d", &n);
      int a = n / 100 % 10, b = n / 10 % 10, c = n % 10;
      int ans = max({
        a*10 + b, // erase c
        a*10 + c, // erase b
        b*10 + c, // erase a
      });
      printf("%d\n", ans);
    }
  return 0;
}