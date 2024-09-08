#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  lli x;
  while (scanf("%lld", &x) != EOF)
  {
    lli curr = 100, ans = 0;
    while (curr < x) curr = curr + (curr / 100), ans++;
    printf("%lld\n", ans);
  }
  return 0;
}